#include <cstdint>

struct alignas(16) xmm_t {
  uint64_t a, b;
};

int main() {
  constexpr uint64_t r8[] = {
    0x0001020304050607,
    0x1011121314151617,
    0x2021222324252627,
    0x3031323334353637,
    0x4041424344454647,
    0x5051525354555657,
    0x6061626364656667,
    0x7071727374757677,
  };

  constexpr xmm_t xmm8[] = {
    { 0x0F0E0D0C0B0A0908, 0x1716151413121110, },
    { 0x100F0E0D0C0B0A09, 0x1817161514131211, },
    { 0x11100F0E0D0C0B0A, 0x1918171615141312, },
    { 0x1211100F0E0D0C0B, 0x1A19181716151413, },
    { 0x131211100F0E0D0C, 0x1B1A191817161514, },
    { 0x14131211100F0E0D, 0x1C1B1A1918171615, },
    { 0x1514131211100F0E, 0x1D1C1B1A19181716, },
    { 0x161514131211100F, 0x1E1D1C1B1A191817, },
  };

  asm volatile(
    "movq     0x00(%%rax), %%r8\n\t"
    "movq     0x08(%%rax), %%r9\n\t"
    "movq     0x10(%%rax), %%r10\n\t"
    "movq     0x18(%%rax), %%r11\n\t"
    "movq     0x20(%%rax), %%r12\n\t"
    "movq     0x28(%%rax), %%r13\n\t"
    "movq     0x30(%%rax), %%r14\n\t"
    "movq     0x38(%%rax), %%r15\n\t"
    "\n\t"
    "movaps   0x00(%%rbx), %%xmm8\n\t"
    "movaps   0x10(%%rbx), %%xmm9\n\t"
    "movaps   0x20(%%rbx), %%xmm10\n\t"
    "movaps   0x30(%%rbx), %%xmm11\n\t"
    "movaps   0x40(%%rbx), %%xmm12\n\t"
    "movaps   0x50(%%rbx), %%xmm13\n\t"
    "movaps   0x60(%%rbx), %%xmm14\n\t"
    "movaps   0x70(%%rbx), %%xmm15\n\t"
    "\n\t"
    "int3\n\t"
    :
    : "a"(r8), "b"(xmm8)
    : "%r8", "%r9", "%r10", "%r11", "%r12", "%r13", "%r14", "%r15", "%xmm8",
      "%xmm9", "%xmm10", "%xmm11", "%xmm12", "%xmm13", "%xmm14", "%xmm15"
  );

  return 0;
}
