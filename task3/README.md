# Lab 2 – Task 3 Logbook

## Objectives
- Capture live microphone samples via Vbuddy and stream them into on-chip RAM.
- Read delayed samples from a second RAM port to visualise a simple echo effect.
- Preserve simultaneous read/write capability without corrupting stored data.

## Design Overview
- Retained the Task 1 counter skeleton to produce sequential RAM write addresses.
- Repurposed the “ROM” concept into a synchronous dual-port RAM (`task3/rom.sv`) with independent write/read addresses.
- Planned top-level module (`sigdelay.sv`) to accept rotary-controlled offset, microphone sample input, and emit delayed output for plotting.

## Implementation Notes

### Counter (`task3/counter.sv`)
- Same asynchronous-reset counter as previous tasks, but hard-wired to increment by one so every sample advances the write pointer.
- Parameterisation still present, keeping address width flexible for future RAM resizing.

### Dual-port RAM (`task3/rom.sv`)
- Acts as RAM despite name; write occurs on `addr1`, read occurs on `addr2` within the same clocked block.
- Single `always_ff` handles both operations; Verilator models write-first behaviour (read returns the newly written value when `addr1 == addr2`).
- Commented reminder (in Chinese) about read/write collision—flagged for further exploration if echo depth shrinks to zero.

### Top-level (`task3/sigdelay.sv`)
- Currently instantiates counter and RAM, wiring `addr` to write port and `addr + incr` to read port.
- Exposes `din`/`dout` pair for microphone input & delayed output.
- Naming mismatch discovered: module is still called `sinegen` even though the file is `sigdelay.sv`. The Verilator model expected by the provided testbench (`Vsigdelay`) requires renaming this module—logged under Issues.

### Testbench (`task3/sigdelay_tb.cpp`)
- Provides the reference integration with Vbuddy microphone APIs:
  - `vbdInitMicIn(RAM_SZ)` reserves buffer space.
  - `vbdMicValue()` feeds `mic_signal` each cycle.
  - `offset` (rotary encoder) steers the read pointer separation.
- Drives separate `wr` and `rd` enables; current RTL lacks these ports, so interface alignment is pending.
- Visualises both input (`mic_signal`) and delayed output (`delayed_signal`) concurrently to show echo.

## Verification Diary
- **Static review:** Confirmed RAM depth set via `ADDRESS_WIDTH`; ready to bump to 9 for 512 samples per lab brief.
- **Interface linting:** Attempted to mentally map testbench expectations to RTL—revealed missing control signals (`wr`, `rd`, `offset`, `mic_signal`, `delayed_signal`).
- **Next run plan:** After renaming module and extending ports, will reuse Task 1/2 flow (`verilator -Wall --cc --trace ...`) and target new executable `Vsigdelay`.

## Issues & Action Items
- **Module naming mismatch:** Must rename module in `sigdelay.sv` to `sigdelay` (or pass `--top-module`) so Verilator matches the generated class.
- **Port mismatch:** Need to add write and read enables plus explicit offset input to align with `sigdelay_tb.cpp`. Present design only uses `en`, `din`, `incr`, and `dout`.
- **Offset arithmetic:** Current implementation uses `addr + incr`. Once `offset` is introduced, ensure arithmetic wraps within the RAM depth (likely by trimming to `COUNT_WIDTH` bits).
- **Read-before-write hazards:** With simultaneous read/write to neighbouring addresses, evaluate whether read-after-write semantics match desired delay (read should observe previous content, not current write).

## Reflections
- The transition from ROM to RAM gives fresh appreciation for how important interface agreements are: unlike read-only memory, RAM now needs explicit control signals and directionality.
- Planning ahead with parameterised widths eased the shift, but naming discipline slipped—good reminder to align filenames, module names, and testbench expectations.
- The provided C++ harness is richer than earlier tasks, handling audio buffers and amplitude plotting; anticipating longer debug cycles once live data flows.
- Looking forward to hearing/visualising the delayed audio once integration is complete; this task bridges theory with tangible DSP behaviour.

## Next Steps
- Rename the top module to `sigdelay`, expand the port list (`wr`, `rd`, `offset`, `mic_signal`, `delayed_signal`), and wire enables through.
- Add saturating address arithmetic or rely on natural overflow—document whichever approach is chosen for future maintainers.
- Consider capturing a short waveform dump to confirm delay length equals rotary-selected offset.
- Once functional, explore storing multiple delay taps or implementing circular buffer read offsets for richer effects.
