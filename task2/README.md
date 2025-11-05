# Lab 2 – Task 2 Logbook

## Objectives
- Extend the Task 1 sine generator to drive two phase-related outputs sourced from a shared dual-port ROM.
- Let the rotary encoder control phase offset live while optionally retiming the base step rate.
- Maintain full compatibility with the Task 1 counter/ROM parameterisation to minimise code churn.

## Migration Summary
- Forked Task 1 assets into `task2/` and validated baseline simulation before introducing dual-output changes.
- Introduced `cnt_incr` input to the top level (`task2/sinegen.sv`) so the counter rate can remain independent from the phase offset knob.
- Reworked ROM interface (`task2/rom.sv`) to present two read ports that share the same clock and memory image.

## Detailed Implementation Notes

### Counter (`task2/counter.sv`)
- Identical to Task 1 version: asynchronous reset, gated increment by `cnt_incr`.
- Continued to keep increment as free-running addition to handle coarse frequency sweeps.

### Dual-port ROM (`task2/rom.sv`)
- Same initialisation flow as Task 1 but now registers two outputs (`dout1`, `dout2`) in the same clocked block.
- Address calculation performed externally; ROM trusts the caller to supply phase-adjusted address already wrapped to 8 bits.
- Observed that `addr1` and `addr2` share the same `rom_array`; Verilator handles concurrent reads gracefully thanks to synchronous semantics.

### Top-level Sine Generator (`task2/sinegen.sv`)
- Counter instantiation unchanged except for `incr(cnt_incr)`: ensures base frequency is tunable without touching phase separation logic.
- Phase address computed as `addr + incr`; addition relies on natural 8-bit overflow to wrap around LUT seamlessly.
- Exposed both `dout1` and `dout2` to the harness for plotting.

### Testbench (`task2/sinegen_tb.cpp`)
- Sets up two-plot mode in Vbuddy, rendering sine (port A) and phase-shifted waveform (port B) simultaneously.
- Uses `vbdFlag()` as a mode switch:
  - Flag low → rotary encoder drives `incr` (phase offset).
  - Flag high → encoder adjusts `cnt_incr` but clamps to 20 to avoid aliasing.
- Each loop toggles `clk` twice, keeping pace with synchronous ROM expectations.
- Continues to support `q` exit; retains VCD hook for debugging though dumps are commented out to save performance.

## Verification Diary
- **Phase sweep sanity:** With `vbdFlag()` low, rotating encoder visibly slid waveform B relative to waveform A; offset 64 produced the expected 90° separation (sine vs cosine).
- **Frequency retune:** Switching to flag-high mode verified that both outputs preserved phase relationship while running faster/slower thanks to shared counter step size.
- **Wraparound check:** Observed that positive offsets beyond 255 wrap correctly due to 8-bit addition; documented to ensure no explicit modulo needed.
- **Tool run:** `task2/run.sh` mirrors Task 1 script; repeated fast compile/run cycles while tuning phase behaviour.

## Issues & Mitigations
- Initial version kept `incr` as counter step; that tied phase offset and frequency together. Refactoring to `cnt_incr` resolved the coupling.
- Encountered quick jitter when rapidly switching flag modes; mitigated by reading `vbdFlag()` once per loop and reusing the result (prevents inconsistent adjustments).
- Considered adding second counter for port B but rejected it—dual-port ROM approach is leaner and guarantees exact phase relationship.

## Reflections
- Dual-port ROM felt natural thanks to earlier parameterisation—just expanded interface without touching datapath widths.
- Relying on unsigned arithmetic simplified wraparound; this lab reinforced comfort with natural overflow semantics in hardware.
- The Vbuddy visual feedback is invaluable; seeing two traces respond in real time made it clear that the phase model behaves as intended.
- Recognised that the ROM is still unsigned amplitude; for quadrature applications a centered (two’s complement) representation might better match downstream mixers.

## Next Steps
- Add optional negative offsets by interpreting encoder value as signed; would enable leading or lagging phase relationships.
- Drop in assertions to confirm that both `cnt_incr` and `incr` stay non-zero to avoid stalling outputs unintentionally.
- Explore parameterising LUT depth to prototype higher-resolution generators without rewriting modules.
- Capture sample plots and measured phase delays into the lab report for documentation completeness.
