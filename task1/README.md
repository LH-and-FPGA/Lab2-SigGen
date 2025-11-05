# Lab 2 – Task 1 Logbook

## Objectives
- Build a single-channel waveform generator that stitches a counter and ROM together.
- Pre-load the lookup table with `sinerom.mem` and exercise the design through a Verilator/Vbuddy testbench.
- Complete the stretch challenge of live frequency control using the rotary encoder.

## Pre-lab Setup
- Confirmed toolchain by running `task1/run.sh` (removes stale `obj_dir`, re-invokes Verilator with tracing, then executes the model).
- Regenerated `sinerom.mem` with `task1/sinegen.py` to double-check the cosine LUT (0–255 range, 16 values per line for readability).
- Reviewed lab brief in `Lab_2.md` to map deliverables to repository layout.

## Implementation Walkthrough

### Counter (`task1/counter.sv`)
- Parameterised width with asynchronous reset (`always_ff @(posedge clk, posedge rst)`), ensuring deterministic start-up when Vbuddy asserts reset mid-run.
- `en` gate pauses the phase accumulator; gating is essential when experimenting with rotary encoder inputs that may momentarily drop to zero.
- Simple increment path keeps resource usage minimal; addition by `incr` enables programmable frequency scaling.

### ROM (`task1/rom.sv`)
- Synchronous read scheme; `$readmemh("sinerom.mem", rom_array)` executed at elaboration, with a diagnostic `$display` to catch missing file issues early.
- Array declared with `2**ADDRESS_WIDTH` depth, so widening the address parameter automatically resizes storage.
- Output registered on the clock edge to align with counter pipeline and ease timing closure in eventual FPGA port.

### Sine Generator Top (`task1/sinegen.sv`)
- Connects the counter output to ROM address; parameter pass-through keeps interface clean.
- Top-level exposes `incr`, `rst`, and `en` so the testbench can model both static frequency selection and interactive experiments.
- No additional glue logic required; synchronous boundaries keep simulation waveforms tidy.

### Testbench Highlights (`task1/sinegen_tb.cpp`)
- Enables tracing via `VerilatedVcdC` for debugging corner cases (e.g., verifying wraparound).
- Integrates Vbuddy UI: `vbdValue()` returns rotary encoder value, `vbdPlot()` visualises the waveform, `vbdGetkey()` offers graceful exit.
- Uses `vbdFlag()` as a mode toggle: when asserted, the encoder simultaneously blips reset and limits `incr` to a safe max (10), effectively fulfilling the lab’s “change frequency” challenge in hardware-friendly increments.
- Maintains continuous simulation loop; intentionally omits `MAX_SIM_CYC` guard to emulate hardware running indefinitely.

## Verification Diary
- **ROM sanity check:** After regenerating `sinerom.mem`, verified the first few entries via quick script inspection—values alternate smoothly around mid-scale (127) confirming cosine profile.
- **Functional sim:** With Vbuddy flag low, observed steady sine trace in Vbuddy window; raising the flag caused counter reset, proving asynchronous reset path.
- **Frequency sweep:** Encoder adjustments between 1 and 10 expanded waveform period as expected. Verified that setting `incr` to 0 halts waveform—logged as potential improvement area.
- **Trace review:** Examined `sinegen.vcd` to confirm single-clock latency between counter and ROM output; ensures later pipelining assumptions hold.

## Issues & Resolutions
- **Asynchronous reset chatter:** Noticed that rapidly toggling `vbdFlag()` induced flicker; added conditional branch to reassert reset only when flag high to stabilise behaviour.
- **Encoder saturation:** Without guard, `vbdValue()` could jump beyond practical range; clamped to 10 to keep increments reasonable, preventing aliasing on LUT.
- **Toolchain hiccup:** Initial Verilator run issued warnings about unused variables due to commented tracing code; documented them for future tidy-up but deemed harmless.

## Reflections
- Parameterisation paid off immediately—no edits required when the ROM width changed later for Task 2.
- Realised that centre-biased sine (two’s complement) might simplify downstream DAC usage; current unsigned format is fine for Vbuddy but less so for audio pipelines.
- Appreciated how Vbuddy scripting accelerates experimentation: no code rebuild needed to sweep frequency, making the lab feel closer to hardware bring-up.
- Keeping ROM synchronous simplified timing but introduces a one-sample delay; acceptable here but worth remembering if phase alignment becomes critical.

## Next Steps
- Add lightweight assertions (SystemVerilog `assert`) to ensure ROM address stays within bounds and reset deassertion clears in one cycle.
- Explore replacing raw rotary value with debounced, rate-limited control to avoid sudden jumps in `incr`.
- Consider exporting waveform samples to CSV alongside VCD for easier plotting in Python/Matlab during write-up.
- Investigate enabling dual-ported ROM even in Task 1 to ease migration to Task 2.
