// SPDX-License-Identifier: Unlicense OR MIT

package layout

import (
	"image"

	"gioui.org/ui"
	"gioui.org/ui/gesture"
	"gioui.org/ui/input"
	"gioui.org/ui/paint"
	"gioui.org/ui/pointer"
)

type scrollChild struct {
	size  image.Point
	macro ui.MacroOp
}

// List displays a subsection of a potentially infinitely
// large underlying list. List accepts user input to scroll
// the subsection.
type List struct {
	Axis Axis
	// Inverted lists stay scrolled to the far end position
	// until the user scrolls away.
	Invert bool
	// Alignment is the cross axis alignment of list elements.
	Alignment Alignment

	// beforeEnd tracks whether the List position is before
	// the very end.
	beforeEnd bool

	config      ui.Config
	ops         *ui.Ops
	queue       input.Queue
	macro       ui.MacroOp
	child       ui.MacroOp
	scroll      gesture.Scroll
	scrollDelta int

	// first is the index of the first visible child.
	first int
	// offset is the signed distance from the top edge
	// to the child with index first.
	offset int

	cs  Constraints
	len int

	// maxSize is the total size of visible children.
	maxSize  int
	children []scrollChild
	dir      iterationDir
}

type iterationDir uint8

const (
	iterateNone iterationDir = iota
	iterateForward
	iterateBackward
)

const inf = 1e6

// Init prepares the list for iterating through its children with Next.
func (l *List) Init(cfg ui.Config, q input.Queue, ops *ui.Ops, cs Constraints, len int) {
	if l.More() {
		panic("unfinished child")
	}
	l.config = cfg
	l.queue = q
	l.update()
	l.ops = ops
	l.maxSize = 0
	l.children = l.children[:0]
	l.cs = cs
	l.len = len
	// Inverted lists scroll to the very end as long as the user hasn't
	// scrolled away.
	if l.scrollToEnd() {
		l.offset = 0
		l.first = len
	}
	if l.first > len {
		l.offset = 0
		l.first = len
	}
	l.macro.Record(ops)
	l.Next()
}

func (l *List) scrollToEnd() bool {
	return l.Invert && !l.beforeEnd
}

// Dragging reports whether the List is being dragged.
func (l *List) Dragging() bool {
	return l.scroll.State() == gesture.StateDragging
}

func (l *List) update() {
	d := l.scroll.Scroll(l.config, l.queue, gesture.Axis(l.Axis))
	l.scrollDelta = d
	l.offset += d
}

// Next advances to the next child.
func (l *List) Next() {
	l.dir = l.next()
	// The user scroll offset is applied after scrolling to
	// list end.
	if l.scrollToEnd() && !l.More() && l.scrollDelta < 0 {
		l.beforeEnd = true
		l.offset += l.scrollDelta
		l.dir = l.next()
	}
	if l.More() {
		l.child.Record(l.ops)
	}
}

// Index is current child's position in the underlying list.
func (l *List) Index() int {
	switch l.dir {
	case iterateBackward:
		return l.first - 1
	case iterateForward:
		return l.first + len(l.children)
	default:
		panic("Index called before Next")
	}
}

// Constraints is the constraints for the current child.
func (l *List) Constraints() Constraints {
	return axisConstraints(l.Axis, Constraint{Max: inf}, axisCrossConstraint(l.Axis, l.cs))
}

// More reports whether more children are needed.
func (l *List) More() bool {
	return l.dir != iterateNone
}

func (l *List) next() iterationDir {
	vsize := axisMainConstraint(l.Axis, l.cs).Max
	last := l.first + len(l.children)
	// Clamp offset.
	if l.maxSize-l.offset < vsize && last == l.len {
		l.offset = l.maxSize - vsize
	}
	if l.offset < 0 && l.first == 0 {
		l.offset = 0
	}
	switch {
	case len(l.children) == l.len:
		return iterateNone
	case l.maxSize-l.offset < vsize:
		return iterateForward
	case l.offset < 0:
		return iterateBackward
	}
	return iterateNone
}

// End the current child by specifying its dimensions.
func (l *List) End(dims Dimensions) {
	l.child.Stop()
	child := scrollChild{dims.Size, l.child}
	mainSize := axisMain(l.Axis, child.size)
	l.maxSize += mainSize
	switch l.dir {
	case iterateForward:
		l.children = append(l.children, child)
	case iterateBackward:
		l.children = append([]scrollChild{child}, l.children...)
		l.first--
		l.offset += mainSize
	default:
		panic("call Next before End")
	}
	l.dir = iterateNone
}

// Layout the List and return its dimensions.
func (l *List) Layout() Dimensions {
	if l.More() {
		panic("unfinished child")
	}
	mainc := axisMainConstraint(l.Axis, l.cs)
	children := l.children
	// Skip invisible children
	for len(children) > 0 {
		sz := children[0].size
		mainSize := axisMain(l.Axis, sz)
		if l.offset <= mainSize {
			break
		}
		l.first++
		l.offset -= mainSize
		children = children[1:]
	}
	size := -l.offset
	var maxCross int
	for i, child := range children {
		sz := child.size
		if c := axisCross(l.Axis, sz); c > maxCross {
			maxCross = c
		}
		size += axisMain(l.Axis, sz)
		if size >= mainc.Max {
			children = children[:i+1]
			break
		}
	}
	ops := l.ops
	pos := -l.offset
	// Inverted lists are end aligned.
	if space := mainc.Max - size; l.Invert && space > 0 {
		pos += space
	}
	for _, child := range children {
		sz := child.size
		var cross int
		switch l.Alignment {
		case End:
			cross = maxCross - axisCross(l.Axis, sz)
		case Middle:
			cross = (maxCross - axisCross(l.Axis, sz)) / 2
		}
		childSize := axisMain(l.Axis, sz)
		max := childSize + pos
		if max > mainc.Max {
			max = mainc.Max
		}
		min := pos
		if min < 0 {
			min = 0
		}
		r := image.Rectangle{
			Min: axisPoint(l.Axis, min, -inf),
			Max: axisPoint(l.Axis, max, inf),
		}
		var stack ui.StackOp
		stack.Push(ops)
		paint.RectClip(r).Add(ops)
		ui.TransformOp{}.Offset(toPointF(axisPoint(l.Axis, pos, cross))).Add(ops)
		child.macro.Add(ops)
		stack.Pop()
		pos += childSize
	}
	atStart := l.first == 0 && l.offset <= 0
	atEnd := l.first+len(children) == l.len && mainc.Max >= pos
	if atStart && l.scrollDelta < 0 || atEnd && l.scrollDelta > 0 {
		l.scroll.Stop()
	}
	l.beforeEnd = !atEnd
	dims := axisPoint(l.Axis, mainc.Constrain(pos), maxCross)
	l.macro.Stop()
	pointer.RectAreaOp{Rect: image.Rectangle{Max: dims}}.Add(ops)
	l.scroll.Add(ops)
	l.macro.Add(ops)
	return Dimensions{Size: dims}
}
