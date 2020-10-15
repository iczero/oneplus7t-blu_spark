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

/*
 * Possible values for "force_fast_charge" are :
 *
 *   0 - Disabled (default)
 *   1 - Force faster charge
*/

/*
 * Options for "dash_charge_mode_override":
 * 0 - do not touch anything (default)
 * 1 - force dash "current limit" mode if it is not already set
 * 2 - force disable dash mode
 */

#include <linux/kobject.h>
#include <linux/sysfs.h>
#include <linux/fastchg.h>
#include <linux/string.h>
#include <linux/module.h>

int force_fast_charge = 0;
int dash_charge_mode_override = FASTCHG_DASH_NO_OPERATION;

static int __init get_fastcharge_opt(char *ffc)
{
	if (strcmp(ffc, "0") == 0) {
		force_fast_charge = 0;
	} else if (strcmp(ffc, "1") == 0) {
		force_fast_charge = 1;
	} else {
		force_fast_charge = 0;
	}
	return 1;
}

__setup("ffc=", get_fastcharge_opt);

static ssize_t force_fast_charge_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
	size_t count = 0;
	count += sprintf(buf, "%d\n", force_fast_charge);
	return count;
}

static ssize_t force_fast_charge_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count)
{
	sscanf(buf, "%d ", &force_fast_charge);
	if (force_fast_charge < 0 || force_fast_charge > 1)
		force_fast_charge = 0;

	return count;
}

static ssize_t dash_override_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf) {
	size_t count = 0;
	count += sprintf(buf, "%d\n", dash_charge_mode_override);
	return count;
}

static ssize_t dash_override_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count) {
	int opt;
	sscanf(buf, "%d ", &opt);
	if (opt < 0 || opt > 2) opt = 0;
	dash_charge_mode_override = opt;
	return count;
}

static struct kobj_attribute force_fast_charge_attribute =
__ATTR(force_fast_charge, 0664, force_fast_charge_show, force_fast_charge_store);
static struct kobj_attribute dash_override_attribute =
__ATTR(dash_charge_mode_override, 0664, dash_override_show, dash_override_store);

static struct attribute *force_fast_charge_attrs[] = {
&force_fast_charge_attribute.attr,
&dash_override_attribute.attr,
NULL,
};

static struct attribute_group force_fast_charge_attr_group = {
.attrs = force_fast_charge_attrs,
};

/* Initialize fast charge sysfs folder */
static struct kobject *force_fast_charge_kobj;

int force_fast_charge_init(void)
{
	int force_fast_charge_retval;

	force_fast_charge_kobj = kobject_create_and_add("fast_charge", kernel_kobj);
	if (!force_fast_charge_kobj) {
			return -ENOMEM;
	}

	force_fast_charge_retval = sysfs_create_group(force_fast_charge_kobj, &force_fast_charge_attr_group);

	if (force_fast_charge_retval)
		kobject_put(force_fast_charge_kobj);

	if (force_fast_charge_retval)
		kobject_put(force_fast_charge_kobj);

	return (force_fast_charge_retval);
}

void force_fast_charge_exit(void)
{
	kobject_put(force_fast_charge_kobj);
}

module_init(force_fast_charge_init);
module_exit(force_fast_charge_exit);
