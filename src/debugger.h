/*
 * This file is part of theodore, a Thomson emulator
 * (https://github.com/Zlika/theodore).
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

/* Rudimentary command-line debugger. */

#ifndef __DEBUGGER_H
#define __DEBUGGER_H

typedef enum
{
  /* Debugger disabled: no disassembly. */
  DEBUG_DISABLED,
  /* Debugger enabled: disassembles and prints all the instructions. */
  DEBUG_RUN,
  /* Step-by-step mode: disassembles and prints an instruction and wait for a keystroke. */
  DEBUG_STEP
} DebuggerMode;

/* Sets the debugger mode. */
void debugger_setMode(DebuggerMode mode);
/* Debug the instruction at the given address. */
void debug(int address);

#endif
