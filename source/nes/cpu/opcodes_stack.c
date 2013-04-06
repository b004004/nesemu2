/***************************************************************************
 *   Copyright (C) 2013 by James Holodnak                                  *
 *   jamesholodnak@gmail.com                                               *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

//push/pop
static INLINE void OP_PHA()
{
	push(A);
}

static INLINE void OP_PHP()
{
	compact_flags();
	push(P);
}

static INLINE void OP_PLA()
{
	memread(SP | 0x100);
	A = pop();
	checknz(A);
}

static INLINE void OP_PLP()
{
	memread(SP | 0x100);
	P = pop();
	expand_flags();
}

//rts/rti
static INLINE void OP_RTS()
{
	memread(SP | 0x100);
	PC = pop();
	PC |= pop() << 8;
	memread(PC++);
}

static INLINE void OP_RTI()
{
	memread(SP | 0x100);
	P = pop();
	expand_flags();
	PC = pop();
	PC |= pop() << 8;
}

//jmp/jsr
static INLINE void OP_JMP()
{
	PC = EFFADDR;
}

static INLINE void OP_JSR()
{
	TMPREG = memread(PC++);
	memread(SP | 0x100);
	push((u8)(PC >> 8));
	push((u8)PC);
	PC = (memread(PC) << 8) | TMPREG;
}

