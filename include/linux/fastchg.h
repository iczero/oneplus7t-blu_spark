/*
 * Author: Chad Froebel <chadfroebel@gmail.com>
 *
 * Port to guacamole: engstk <eng.stk@sapo.pt>
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#ifndef _LINUX_FASTCHG_H
#define _LINUX_FASTCHG_H

extern int force_fast_charge;

#define FASTCHG_DASH_NO_OPERATION 0
#define FASTCHG_DASH_FORCE_CURRENT_LIMIT 1
#define FASTCHG_DASH_FORCE_DISABLE 2
// allow limiting current or disabling dash through sysfs
extern int dash_charge_mode_override;

#endif
