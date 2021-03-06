// SPDX-License-Identifier: Apache-2.0 OR MIT OR Unlicense

// Code auto-generated by piet-gpu-derive

struct AnnoFillRef {
    uint offset;
};

struct AnnoFillTextureRef {
    uint offset;
};

struct AnnoStrokeRef {
    uint offset;
};

struct AnnoClipRef {
    uint offset;
};

struct AnnotatedRef {
    uint offset;
};

struct AnnoFill {
    vec4 bbox;
    uint rgba_color;
};

#define AnnoFill_size 20

AnnoFillRef AnnoFill_index(AnnoFillRef ref, uint index) {
    return AnnoFillRef(ref.offset + index * AnnoFill_size);
}

struct AnnoFillTexture {
    vec4 bbox;
    vec4 mat;
    vec2 translate;
    uvec2 uv_bounds;
};

#define AnnoFillTexture_size 48

AnnoFillTextureRef AnnoFillTexture_index(AnnoFillTextureRef ref, uint index) {
    return AnnoFillTextureRef(ref.offset + index * AnnoFillTexture_size);
}

struct AnnoStroke {
    vec4 bbox;
    uint rgba_color;
    float linewidth;
};

#define AnnoStroke_size 24

AnnoStrokeRef AnnoStroke_index(AnnoStrokeRef ref, uint index) {
    return AnnoStrokeRef(ref.offset + index * AnnoStroke_size);
}

struct AnnoClip {
    vec4 bbox;
};

#define AnnoClip_size 16

AnnoClipRef AnnoClip_index(AnnoClipRef ref, uint index) {
    return AnnoClipRef(ref.offset + index * AnnoClip_size);
}

#define Annotated_Nop 0
#define Annotated_Stroke 1
#define Annotated_Fill 2
#define Annotated_FillTexture 3
#define Annotated_BeginClip 4
#define Annotated_EndClip 5
#define Annotated_size 52

AnnotatedRef Annotated_index(AnnotatedRef ref, uint index) {
    return AnnotatedRef(ref.offset + index * Annotated_size);
}

AnnoFill AnnoFill_read(Alloc a, AnnoFillRef ref) {
    uint ix = ref.offset >> 2;
    uint raw0 = read_mem(a, ix + 0);
    uint raw1 = read_mem(a, ix + 1);
    uint raw2 = read_mem(a, ix + 2);
    uint raw3 = read_mem(a, ix + 3);
    uint raw4 = read_mem(a, ix + 4);
    AnnoFill s;
    s.bbox = vec4(uintBitsToFloat(raw0), uintBitsToFloat(raw1), uintBitsToFloat(raw2), uintBitsToFloat(raw3));
    s.rgba_color = raw4;
    return s;
}

void AnnoFill_write(Alloc a, AnnoFillRef ref, AnnoFill s) {
    uint ix = ref.offset >> 2;
    write_mem(a, ix + 0, floatBitsToUint(s.bbox.x));
    write_mem(a, ix + 1, floatBitsToUint(s.bbox.y));
    write_mem(a, ix + 2, floatBitsToUint(s.bbox.z));
    write_mem(a, ix + 3, floatBitsToUint(s.bbox.w));
    write_mem(a, ix + 4, s.rgba_color);
}

AnnoFillTexture AnnoFillTexture_read(Alloc a, AnnoFillTextureRef ref) {
    uint ix = ref.offset >> 2;
    uint raw0 = read_mem(a, ix + 0);
    uint raw1 = read_mem(a, ix + 1);
    uint raw2 = read_mem(a, ix + 2);
    uint raw3 = read_mem(a, ix + 3);
    uint raw4 = read_mem(a, ix + 4);
    uint raw5 = read_mem(a, ix + 5);
    uint raw6 = read_mem(a, ix + 6);
    uint raw7 = read_mem(a, ix + 7);
    uint raw8 = read_mem(a, ix + 8);
    uint raw9 = read_mem(a, ix + 9);
    uint raw10 = read_mem(a, ix + 10);
    uint raw11 = read_mem(a, ix + 11);
    AnnoFillTexture s;
    s.bbox = vec4(uintBitsToFloat(raw0), uintBitsToFloat(raw1), uintBitsToFloat(raw2), uintBitsToFloat(raw3));
    s.mat = vec4(uintBitsToFloat(raw4), uintBitsToFloat(raw5), uintBitsToFloat(raw6), uintBitsToFloat(raw7));
    s.translate = vec2(uintBitsToFloat(raw8), uintBitsToFloat(raw9));
    s.uv_bounds = uvec2(raw10, raw11);
    return s;
}

void AnnoFillTexture_write(Alloc a, AnnoFillTextureRef ref, AnnoFillTexture s) {
    uint ix = ref.offset >> 2;
    write_mem(a, ix + 0, floatBitsToUint(s.bbox.x));
    write_mem(a, ix + 1, floatBitsToUint(s.bbox.y));
    write_mem(a, ix + 2, floatBitsToUint(s.bbox.z));
    write_mem(a, ix + 3, floatBitsToUint(s.bbox.w));
    write_mem(a, ix + 4, floatBitsToUint(s.mat.x));
    write_mem(a, ix + 5, floatBitsToUint(s.mat.y));
    write_mem(a, ix + 6, floatBitsToUint(s.mat.z));
    write_mem(a, ix + 7, floatBitsToUint(s.mat.w));
    write_mem(a, ix + 8, floatBitsToUint(s.translate.x));
    write_mem(a, ix + 9, floatBitsToUint(s.translate.y));
    write_mem(a, ix + 10, s.uv_bounds.x);
    write_mem(a, ix + 11, s.uv_bounds.y);
}

AnnoStroke AnnoStroke_read(Alloc a, AnnoStrokeRef ref) {
    uint ix = ref.offset >> 2;
    uint raw0 = read_mem(a, ix + 0);
    uint raw1 = read_mem(a, ix + 1);
    uint raw2 = read_mem(a, ix + 2);
    uint raw3 = read_mem(a, ix + 3);
    uint raw4 = read_mem(a, ix + 4);
    uint raw5 = read_mem(a, ix + 5);
    AnnoStroke s;
    s.bbox = vec4(uintBitsToFloat(raw0), uintBitsToFloat(raw1), uintBitsToFloat(raw2), uintBitsToFloat(raw3));
    s.rgba_color = raw4;
    s.linewidth = uintBitsToFloat(raw5);
    return s;
}

void AnnoStroke_write(Alloc a, AnnoStrokeRef ref, AnnoStroke s) {
    uint ix = ref.offset >> 2;
    write_mem(a, ix + 0, floatBitsToUint(s.bbox.x));
    write_mem(a, ix + 1, floatBitsToUint(s.bbox.y));
    write_mem(a, ix + 2, floatBitsToUint(s.bbox.z));
    write_mem(a, ix + 3, floatBitsToUint(s.bbox.w));
    write_mem(a, ix + 4, s.rgba_color);
    write_mem(a, ix + 5, floatBitsToUint(s.linewidth));
}

AnnoClip AnnoClip_read(Alloc a, AnnoClipRef ref) {
    uint ix = ref.offset >> 2;
    uint raw0 = read_mem(a, ix + 0);
    uint raw1 = read_mem(a, ix + 1);
    uint raw2 = read_mem(a, ix + 2);
    uint raw3 = read_mem(a, ix + 3);
    AnnoClip s;
    s.bbox = vec4(uintBitsToFloat(raw0), uintBitsToFloat(raw1), uintBitsToFloat(raw2), uintBitsToFloat(raw3));
    return s;
}

void AnnoClip_write(Alloc a, AnnoClipRef ref, AnnoClip s) {
    uint ix = ref.offset >> 2;
    write_mem(a, ix + 0, floatBitsToUint(s.bbox.x));
    write_mem(a, ix + 1, floatBitsToUint(s.bbox.y));
    write_mem(a, ix + 2, floatBitsToUint(s.bbox.z));
    write_mem(a, ix + 3, floatBitsToUint(s.bbox.w));
}

uint Annotated_tag(Alloc a, AnnotatedRef ref) {
    return read_mem(a, ref.offset >> 2);
}

AnnoStroke Annotated_Stroke_read(Alloc a, AnnotatedRef ref) {
    return AnnoStroke_read(a, AnnoStrokeRef(ref.offset + 4));
}

AnnoFill Annotated_Fill_read(Alloc a, AnnotatedRef ref) {
    return AnnoFill_read(a, AnnoFillRef(ref.offset + 4));
}

AnnoFillTexture Annotated_FillTexture_read(Alloc a, AnnotatedRef ref) {
    return AnnoFillTexture_read(a, AnnoFillTextureRef(ref.offset + 4));
}

AnnoClip Annotated_BeginClip_read(Alloc a, AnnotatedRef ref) {
    return AnnoClip_read(a, AnnoClipRef(ref.offset + 4));
}

AnnoClip Annotated_EndClip_read(Alloc a, AnnotatedRef ref) {
    return AnnoClip_read(a, AnnoClipRef(ref.offset + 4));
}

void Annotated_Nop_write(Alloc a, AnnotatedRef ref) {
    write_mem(a, ref.offset >> 2, Annotated_Nop);
}

void Annotated_Stroke_write(Alloc a, AnnotatedRef ref, AnnoStroke s) {
    write_mem(a, ref.offset >> 2, Annotated_Stroke);
    AnnoStroke_write(a, AnnoStrokeRef(ref.offset + 4), s);
}

void Annotated_Fill_write(Alloc a, AnnotatedRef ref, AnnoFill s) {
    write_mem(a, ref.offset >> 2, Annotated_Fill);
    AnnoFill_write(a, AnnoFillRef(ref.offset + 4), s);
}

void Annotated_FillTexture_write(Alloc a, AnnotatedRef ref, AnnoFillTexture s) {
    write_mem(a, ref.offset >> 2, Annotated_FillTexture);
    AnnoFillTexture_write(a, AnnoFillTextureRef(ref.offset + 4), s);
}

void Annotated_BeginClip_write(Alloc a, AnnotatedRef ref, AnnoClip s) {
    write_mem(a, ref.offset >> 2, Annotated_BeginClip);
    AnnoClip_write(a, AnnoClipRef(ref.offset + 4), s);
}

void Annotated_EndClip_write(Alloc a, AnnotatedRef ref, AnnoClip s) {
    write_mem(a, ref.offset >> 2, Annotated_EndClip);
    AnnoClip_write(a, AnnoClipRef(ref.offset + 4), s);
}

