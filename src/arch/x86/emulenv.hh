/*
 * Copyright (c) 2007 The Hewlett-Packard Development Company
 * All rights reserved.
 *
 * The license below extends only to copyright in the software and shall
 * not be construed as granting a license to any other intellectual
 * property including but not limited to intellectual property relating
 * to a hardware implementation of the functionality of the software
 * licensed hereunder.  You may use the software subject to the license
 * terms below provided that you ensure that this notice is replicated
 * unmodified and in its entirety in all distributions of the software,
 * modified or unmodified, in source code or in binary form.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met: redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer;
 * redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution;
 * neither the name of the copyright holders nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __ARCH_X86_EMULENV_HH__
#define __ARCH_X86_EMULENV_HH__

#include "arch/x86/regs/int.hh"
#include "arch/x86/regs/segment.hh"
#include "arch/x86/registers.hh"
#include "arch/x86/types.hh"

namespace X86ISA
{
    struct EmulEnv
    {
        RegIndex reg1;
        RegIndex reg2;
        RegIndex regm;
        RegIndex reg4;
        RegIndex opmask;
        SegmentRegIndex seg;
        uint8_t scale;
        RegIndex index;
        RegIndex vindex;
        RegIndex base;
        int dataSize;
        int addressSize;
        int stackSize;

        EmulEnv(RegIndex _reg1, RegIndex _regm,
                int _dataSize, int _addressSize, int _stackSize) :
            reg1(_reg1), regm(_regm),
            seg(SEGMENT_REG_DS), scale(0),
            index(NUM_INTREGS), vindex(NUM_INTREGS), base(NUM_INTREGS),
            dataSize(_dataSize), addressSize(_addressSize),
            stackSize(_stackSize)
        {;}

        EmulEnv(RegIndex _reg1, RegIndex _reg2, RegIndex _regm,
                int _dataSize, int _addressSize, int _stackSize) :
            reg1(_reg1), reg2(_reg2), regm(_regm),
            seg(SEGMENT_REG_DS), scale(0),
            index(NUM_INTREGS), vindex(NUM_INTREGS), base(NUM_INTREGS),
            dataSize(_dataSize), addressSize(_addressSize),
            stackSize(_stackSize)
        {;}

        EmulEnv(RegIndex _reg1, RegIndex _reg2, RegIndex _regm,
                RegIndex _reg4,
                int _dataSize, int _addressSize, int _stackSize) :
            reg1(_reg1), reg2(_reg2), regm(_regm), reg4(_reg4),
            seg(SEGMENT_REG_DS), scale(0), index(NUM_INTREGS),
            vindex(NUM_INTREGS), base(NUM_INTREGS),
            dataSize(_dataSize), addressSize(_addressSize),
            stackSize(_stackSize)
        {;}

        void doModRM(const ExtMachInst & machInst);
        void setSeg(const ExtMachInst & machInst);
    };

    struct OpMaskEmulEnv : EmulEnv
    {
        OpMaskEmulEnv(RegIndex _reg1, RegIndex _regm,
                RegIndex _opmask,
                int _dataSize, int _addressSize, int _stackSize) :
            EmulEnv(_reg1, _regm, _dataSize, _addressSize, _stackSize)
        { opmask = _opmask; }

        OpMaskEmulEnv(RegIndex _reg1, RegIndex _reg2, RegIndex _regm,
                RegIndex _opmask,
                int _dataSize, int _addressSize, int _stackSize) :
            EmulEnv(_reg1, _reg2, _regm, _dataSize, _addressSize, _stackSize)
        { opmask = _opmask; }

        OpMaskEmulEnv(RegIndex _reg1, RegIndex _reg2, RegIndex _regm,
                RegIndex _reg4, RegIndex _opmask,
                int _dataSize, int _addressSize, int _stackSize) :
            EmulEnv(_reg1, _reg2, _regm, _reg4, _dataSize, _addressSize, _stackSize)
        { opmask = _opmask; }
    };
}

#endif // __ARCH_X86_TYPES_HH__
