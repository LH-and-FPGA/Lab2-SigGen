// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vsinegen.h for the primary calling header

#include "Vsinegen__pch.h"
#include "Vsinegen___024root.h"

void Vsinegen___024root___eval_act(Vsinegen___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsinegen__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsinegen___024root___eval_act\n"); );
}

VL_INLINE_OPT void Vsinegen___024root___nba_sequent__TOP__0(Vsinegen___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsinegen__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsinegen___024root___nba_sequent__TOP__0\n"); );
    // Body
    vlSelf->__Vdly__sinegen__DOT__addr = vlSelf->sinegen__DOT__addr;
    if (vlSelf->rst) {
        vlSelf->__Vdly__sinegen__DOT__addr = 0U;
    } else if (vlSelf->en) {
        vlSelf->__Vdly__sinegen__DOT__addr = (0xffU 
                                              & ((IData)(vlSelf->sinegen__DOT__addr) 
                                                 + (IData)(vlSelf->incr)));
    }
}

VL_INLINE_OPT void Vsinegen___024root___nba_sequent__TOP__1(Vsinegen___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsinegen__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsinegen___024root___nba_sequent__TOP__1\n"); );
    // Body
    vlSelf->dout1 = vlSelf->sinegen__DOT__Rom__DOT__rom_array
        [vlSelf->sinegen__DOT__addr];
    vlSelf->dout2 = vlSelf->sinegen__DOT__Rom__DOT__rom_array
        [(0xffU & ((IData)(vlSelf->incr) + (IData)(vlSelf->sinegen__DOT__addr)))];
}

VL_INLINE_OPT void Vsinegen___024root___nba_sequent__TOP__2(Vsinegen___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsinegen__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsinegen___024root___nba_sequent__TOP__2\n"); );
    // Body
    vlSelf->sinegen__DOT__addr = vlSelf->__Vdly__sinegen__DOT__addr;
}

void Vsinegen___024root___eval_nba(Vsinegen___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsinegen__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsinegen___024root___eval_nba\n"); );
    // Body
    if ((1ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsinegen___024root___nba_sequent__TOP__0(vlSelf);
    }
    if ((2ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsinegen___024root___nba_sequent__TOP__1(vlSelf);
    }
    if ((1ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsinegen___024root___nba_sequent__TOP__2(vlSelf);
    }
}

void Vsinegen___024root___eval_triggers__act(Vsinegen___024root* vlSelf);

bool Vsinegen___024root___eval_phase__act(Vsinegen___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsinegen__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsinegen___024root___eval_phase__act\n"); );
    // Init
    VlTriggerVec<2> __VpreTriggered;
    CData/*0:0*/ __VactExecute;
    // Body
    Vsinegen___024root___eval_triggers__act(vlSelf);
    __VactExecute = vlSelf->__VactTriggered.any();
    if (__VactExecute) {
        __VpreTriggered.andNot(vlSelf->__VactTriggered, vlSelf->__VnbaTriggered);
        vlSelf->__VnbaTriggered.thisOr(vlSelf->__VactTriggered);
        Vsinegen___024root___eval_act(vlSelf);
    }
    return (__VactExecute);
}

bool Vsinegen___024root___eval_phase__nba(Vsinegen___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsinegen__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsinegen___024root___eval_phase__nba\n"); );
    // Init
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = vlSelf->__VnbaTriggered.any();
    if (__VnbaExecute) {
        Vsinegen___024root___eval_nba(vlSelf);
        vlSelf->__VnbaTriggered.clear();
    }
    return (__VnbaExecute);
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vsinegen___024root___dump_triggers__nba(Vsinegen___024root* vlSelf);
#endif  // VL_DEBUG
#ifdef VL_DEBUG
VL_ATTR_COLD void Vsinegen___024root___dump_triggers__act(Vsinegen___024root* vlSelf);
#endif  // VL_DEBUG

void Vsinegen___024root___eval(Vsinegen___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsinegen__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsinegen___024root___eval\n"); );
    // Init
    IData/*31:0*/ __VnbaIterCount;
    CData/*0:0*/ __VnbaContinue;
    // Body
    __VnbaIterCount = 0U;
    __VnbaContinue = 1U;
    while (__VnbaContinue) {
        if (VL_UNLIKELY((0x64U < __VnbaIterCount))) {
#ifdef VL_DEBUG
            Vsinegen___024root___dump_triggers__nba(vlSelf);
#endif
            VL_FATAL_MT("sinegen.sv", 1, "", "NBA region did not converge.");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        __VnbaContinue = 0U;
        vlSelf->__VactIterCount = 0U;
        vlSelf->__VactContinue = 1U;
        while (vlSelf->__VactContinue) {
            if (VL_UNLIKELY((0x64U < vlSelf->__VactIterCount))) {
#ifdef VL_DEBUG
                Vsinegen___024root___dump_triggers__act(vlSelf);
#endif
                VL_FATAL_MT("sinegen.sv", 1, "", "Active region did not converge.");
            }
            vlSelf->__VactIterCount = ((IData)(1U) 
                                       + vlSelf->__VactIterCount);
            vlSelf->__VactContinue = 0U;
            if (Vsinegen___024root___eval_phase__act(vlSelf)) {
                vlSelf->__VactContinue = 1U;
            }
        }
        if (Vsinegen___024root___eval_phase__nba(vlSelf)) {
            __VnbaContinue = 1U;
        }
    }
}

#ifdef VL_DEBUG
void Vsinegen___024root___eval_debug_assertions(Vsinegen___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsinegen__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsinegen___024root___eval_debug_assertions\n"); );
    // Body
    if (VL_UNLIKELY((vlSelf->rst & 0xfeU))) {
        Verilated::overWidthError("rst");}
    if (VL_UNLIKELY((vlSelf->en & 0xfeU))) {
        Verilated::overWidthError("en");}
    if (VL_UNLIKELY((vlSelf->clk & 0xfeU))) {
        Verilated::overWidthError("clk");}
}
#endif  // VL_DEBUG
