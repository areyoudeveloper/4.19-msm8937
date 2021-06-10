/*
 * External Connector (extcon) framework
 * - linux/include/linux/extcon.h for extcon consumer device driver.
 *
 * Copyright (C) 2015 Samsung Electronics
 * Author: Chanwoo Choi <cw00.choi@samsung.com>
 *
 * Copyright (C) 2012 Samsung Electronics
 * Author: Donggeun Kim <dg77.kim@samsung.com>
 * Author: MyungJoo Ham <myungjoo.ham@samsung.com>
 *
 * based on switch class driver
 * Copyright (C) 2008 Google, Inc.
 * Author: Mike Lockwood <lockwood@android.com>
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#ifndef __LINUX_EXTCON_H__
#define __LINUX_EXTCON_H__

#include <linux/device.h>

/*
 * Define the type of supported external connectors
 */
#define EXTCON_TYPE_USB		BIT(0)	/* USB connector */
#define EXTCON_TYPE_CHG		BIT(1)	/* Charger connector */
#define EXTCON_TYPE_JACK	BIT(2)	/* Jack connector */
#define EXTCON_TYPE_DISP	BIT(3)	/* Display connector */
#define EXTCON_TYPE_MISC	BIT(4)	/* Miscellaneous connector */

/*
 * Define the unique id of supported external connectors
 */
#define EXTCON_NONE		0

/* USB external connector */
#define EXTCON_USB		1
#define EXTCON_USB_HOST		2

/*
 * Charging external connector
 *
 * When one SDP charger connector was reported, we should also report
 * the USB connector, which means EXTCON_CHG_USB_SDP should always
 * appear together with EXTCON_USB. The same as ACA charger connector,
 * EXTCON_CHG_USB_ACA would normally appear with EXTCON_USB_HOST.
 *
 * The EXTCON_CHG_USB_SLOW connector can provide at least 500mA of
 * current at 5V. The EXTCON_CHG_USB_FAST connector can provide at
 * least 1A of current at 5V.
 */
#define EXTCON_CHG_USB_SDP	5	/* Standard Downstream Port */
#define EXTCON_CHG_USB_DCP	6	/* Dedicated Charging Port */
#define EXTCON_CHG_USB_CDP	7	/* Charging Downstream Port */
#define EXTCON_CHG_USB_ACA	8	/* Accessory Charger Adapter */
#define EXTCON_CHG_USB_FAST	9
#define EXTCON_CHG_USB_SLOW	10
#define EXTCON_CHG_WPT		11	/* Wireless Power Transfer */
#define EXTCON_CHG_USB_PD	12	/* USB Power Delivery */

/* Jack external connector */
#define EXTCON_JACK_MICROPHONE	20
#define EXTCON_JACK_HEADPHONE	21
#define EXTCON_JACK_LINE_IN	22
#define EXTCON_JACK_LINE_OUT	23
#define EXTCON_JACK_VIDEO_IN	24
#define EXTCON_JACK_VIDEO_OUT	25
#define EXTCON_JACK_SPDIF_IN	26	/* Sony Philips Digital InterFace */
#define EXTCON_JACK_SPDIF_OUT	27

/* Display external connector */
#define EXTCON_DISP_HDMI	40	/* High-Definition Multimedia Interface */
#define EXTCON_DISP_MHL		41	/* Mobile High-Definition Link */
#define EXTCON_DISP_DVI		42	/* Digital Visual Interface */
#define EXTCON_DISP_VGA		43	/* Video Graphics Array */
#define EXTCON_DISP_DP		44	/* Display Port */
#define EXTCON_DISP_HMD		45	/* Head-Mounted Display */

/* Miscellaneous external connector */
#define EXTCON_DOCK		60
#define EXTCON_JIG		61
#define EXTCON_MECHANICAL	62

#define EXTCON_NUM		63

/*
 * Define the properties of supported external connectors.
 *
 * When adding the new extcon property, they *must* have
 * the type/value/default information. Also, you *have to*
 * modify the EXTCON_PROP_[type]_START/END definitions
 * which mean the range of the supported properties
 * for each extcon type.
 *
 * The naming style of property
 * : EXTCON_PROP_[type]_[property name]
 *
 * EXTCON_PROP_USB_[property name]	: USB property
 * EXTCON_PROP_CHG_[property name]	: Charger property
 * EXTCON_PROP_JACK_[property name]	: Jack property
 * EXTCON_PROP_DISP_[property name]	: Display property
 */

/*
 * Properties of EXTCON_TYPE_USB.
 *
 * - EXTCON_PROP_USB_VBUS
 * @type:	integer (intval)
 * @value:	0 (low) or 1 (high)
 * @default:	0 (low)
 * - EXTCON_PROP_USB_TYPEC_POLARITY
 * @type:	integer (intval)
 * @value:	0 (normal) or 1 (flip)
 * @default:	0 (normal)
 * - EXTCON_PROP_USB_SS (SuperSpeed)
 * @type:       integer (intval)
 * @value:      0 (USB/USB2) or 1 (USB3)
 * @default:    0 (USB/USB2)
 * - EXTCON_PROP_USB_TYPEC_MED_HIGH_CURRENT
 * @type:       integer (intval)
 * @value:      0 (default current), 1 (medium or high current)
 * @default:    0 (default current)
 *
 */
#define EXTCON_PROP_USB_VBUS		0
#define EXTCON_PROP_USB_TYPEC_POLARITY	1
#define EXTCON_PROP_USB_SS		2
#define EXTCON_PROP_USB_TYPEC_MED_HIGH_CURRENT	3

#define EXTCON_PROP_USB_MIN		0
#define EXTCON_PROP_USB_MAX		3
#define EXTCON_PROP_USB_CNT	(EXTCON_PROP_USB_MAX - EXTCON_PROP_USB_MIN + 1)

/* Properties of EXTCON_TYPE_CHG. */
#define EXTCON_PROP_CHG_MIN		50
#define EXTCON_PROP_CHG_MAX		50
#define EXTCON_PROP_CHG_CNT	(EXTCON_PROP_CHG_MAX - EXTCON_PROP_CHG_MIN + 1)

/* Properties of EXTCON_TYPE_JACK. */
#define EXTCON_PROP_JACK_MIN		100
#define EXTCON_PROP_JACK_MAX		100
#define EXTCON_PROP_JACK_CNT (EXTCON_PROP_JACK_MAX - EXTCON_PROP_JACK_MIN + 1)

/*
 * Properties of EXTCON_TYPE_DISP.
 *
 * - EXTCON_PROP_DISP_HPD (Hot Plug Detect)
 * @type:       integer (intval)
 * @value:      0 (no hpd) or 1 (hpd)
 * @default:    0 (no hpd)
 *
 */
#define EXTCON_PROP_DISP_HPD		150

/* Properties of EXTCON_TYPE_DISP. */
#define EXTCON_PROP_DISP_MIN		150
#define EXTCON_PROP_DISP_MAX		151
#define EXTCON_PROP_DISP_CNT (EXTCON_PROP_DISP_MAX - EXTCON_PROP_DISP_MIN + 1)

/*
 * Define the type of property's value.
 *
 * Define the property's value as union type. Because each property
 * would need the different data type to store it.
 */
union extcon_property_value {
	int intval;	/* type : integer (intval) */
};


struct extcon_cable;

/**
 * struct extcon_dev - An extcon device represents one external connector.
 * @name:		The name of this extcon device. Parent device name is
 *			used if NULL.
 * @supported_cable:	Array of supported cable names ending with EXTCON_NONE.
 *			If supported_cable is NULL, cable name related APIs
 *			are disabled.
 * @mutually_exclusive:	Array of mutually exclusive set of cables that cannot
 *			be attached simultaneously. The array should be
 *			ending with NULL or be NULL (no mutually exclusive
 *			cables). For example, if it is { 0x7, 0x30, 0}, then,
 *			{0, 1}, {0, 1, 2}, {0, 2}, {1, 2}, or {4, 5} cannot
 *			be attached simulataneously. {0x7, 0} is equivalent to
 *			{0x3, 0x6, 0x5, 0}. If it is {0xFFFFFFFF, 0}, there
 *			can be no simultaneous connections.
 * @dev:		Device of this extcon.
 * @state:		Attach/detach state of this extcon. Do not provide at
 *			register-time.
 * @nh:			Notifier for the state change events from this extcon
 * @entry:		To support list of extcon devices so that users can
 *			search for extcon devices based on the extcon name.
 * @lock:
 * @max_supported:	Internal value to store the number of cables.
 * @extcon_dev_type:	Device_type struct to provide attribute_groups
 *			customized for each extcon device.
 * @cables:		Sysfs subdirectories. Each represents one cable.
 *
 * In most cases, users only need to provide "User initializing data" of
 * this struct when registering an extcon. In some exceptional cases,
 * optional callbacks may be needed. However, the values in "internal data"
 * are overwritten by register function.
 */
struct extcon_dev {
	/* Optional user initializing data */
	const char *name;
	const unsigned int *supported_cable;
	const u32 *mutually_exclusive;

	/* Internal data. Please do not set. */
	struct device dev;
	struct raw_notifier_head *nh;
	struct blocking_notifier_head *bnh;
	struct list_head entry;
	int max_supported;
	spinlock_t lock;	/* could be called by irq handler */
	u32 state;

	/* /sys/class/extcon/.../cable.n/... */
	struct device_type extcon_dev_type;
	struct extcon_cable *cables;

	/* /sys/class/extcon/.../mutually_exclusive/... */
	struct attribute_group attr_g_muex;
	struct attribute **attrs_muex;
	struct device_attribute *d_attrs_muex;
};

#if IS_ENABLED(CONFIG_EXTCON)
/*
 * Following APIs get the connected state of each external connector.
 * The 'id' argument indicates the defined external connector.
 */
extern int extcon_get_state(struct extcon_dev *edev, unsigned int id);
extern int devm_extcon_dev_register(struct device *dev,
				    struct extcon_dev *edev);
/*
 * Following APIs get the property of each external connector.
 * The 'id' argument indicates the defined external connector
 * and the 'prop' indicates the extcon property.
 *
 * And extcon_get_property_capability() get the capability of the property
 * for each external connector. They are used to get the capability of the
 * property of each external connector based on the id and property.
 */
extern int extcon_get_property(struct extcon_dev *edev, unsigned int id,
				unsigned int prop,
				union extcon_property_value *prop_val);
extern int extcon_get_property_capability(struct extcon_dev *edev,
				unsigned int id, unsigned int prop);

/*
 * Following APIs set array of mutually exclusive.
 * The 'exclusive' argument indicates the array of mutually exclusive set
 * of cables that cannot be attached simultaneously.
 */
extern int extcon_set_mutually_exclusive(struct extcon_dev *edev,
				const u32 *exclusive);

/*
 * Following APIs register the notifier block in order to detect
 * the change of both state and property value for each external connector.
 *
 * extcon_register_notifier(*edev, id, *nb) : Register a notifier block
 *			for specific external connector of the extcon.
 * extcon_register_notifier_all(*edev, *nb) : Register a notifier block
 *			for all supported external connectors of the extcon.
 */
extern int extcon_register_notifier(struct extcon_dev *edev, unsigned int id,
				struct notifier_block *nb);
extern int extcon_unregister_notifier(struct extcon_dev *edev, unsigned int id,
				struct notifier_block *nb);
extern int extcon_register_blocking_notifier(struct extcon_dev *edev,
		unsigned int id, struct notifier_block *nb);
extern int extcon_unregister_blocking_notifier(struct extcon_dev *edev,
		unsigned int id, struct notifier_block *nb);
extern int devm_extcon_register_notifier(struct device *dev,
				struct extcon_dev *edev, unsigned int id,
				struct notifier_block *nb);
extern void devm_extcon_unregister_notifier(struct device *dev,
				struct extcon_dev *edev, unsigned int id,
				struct notifier_block *nb);

extern int extcon_register_notifier_all(struct extcon_dev *edev,
				struct notifier_block *nb);
extern int extcon_unregister_notifier_all(struct extcon_dev *edev,
				struct notifier_block *nb);
extern int devm_extcon_register_notifier_all(struct device *dev,
				struct extcon_dev *edev,
				struct notifier_block *nb);
extern void devm_extcon_unregister_notifier_all(struct device *dev,
				struct extcon_dev *edev,
				struct notifier_block *nb);

/*
 * Following APIs get the extcon_dev from devicetree or by through extcon name.
 */
extern struct extcon_dev *extcon_get_extcon_dev(const char *extcon_name);
extern struct extcon_dev *extcon_find_edev_by_node(struct device_node *node);
extern struct extcon_dev *extcon_get_edev_by_phandle(struct device *dev,
						     int index);
/*
 * get/set_state access each bit of the 32b encoded state value.
 * They are used to access the status of each cable based on the cable id.
 */
extern int extcon_get_state(struct extcon_dev *edev, unsigned int id);
extern int extcon_set_state(struct extcon_dev *edev, unsigned int id,
				   bool cable_state);
extern int extcon_set_state_sync(struct extcon_dev *edev, unsigned int id,
				bool cable_state);
extern struct extcon_dev *devm_extcon_dev_allocate(struct device *dev,
						   const unsigned int *cable);
/*
 * get/set_property access the property value of each external connector.
 * They are used to access the property of each cable based on the property id.
 */
extern int extcon_get_property(struct extcon_dev *edev, unsigned int id,
				unsigned int prop,
				union extcon_property_value *prop_val);
extern int extcon_set_property(struct extcon_dev *edev, unsigned int id,
				unsigned int prop,
				union extcon_property_value prop_val);
extern int extcon_set_property_sync(struct extcon_dev *edev, unsigned int id,
				unsigned int prop,
				union extcon_property_value prop_val);

/*
 *
/* Following API get the name of extcon device. */
extern const char *extcon_get_edev_name(struct extcon_dev *edev);

extern int extcon_blocking_sync(struct extcon_dev *edev, unsigned int id,
							u8 val);
#else /* CONFIG_EXTCON */
static inline struct extcon_dev *devm_extcon_dev_allocate(struct device *dev,
						const unsigned int *cable)
{
	return ERR_PTR(-ENOSYS);
}


static inline int devm_extcon_dev_register(struct device *dev,
					   struct extcon_dev *edev)
{
	return -EINVAL;
}

static inline int extcon_get_state(struct extcon_dev *edev, unsigned int id)
{
	return 0;
}

static inline int extcon_get_property(struct extcon_dev *edev, unsigned int id,
				unsigned int prop,
				union extcon_property_value *prop_val)
{
	return 0;
}

static inline int extcon_get_property_capability(struct extcon_dev *edev,
				unsigned int id, unsigned int prop)
{
	return 0;
}

static inline int extcon_register_notifier(struct extcon_dev *edev,
				unsigned int id, struct notifier_block *nb)
{
	return 0;
}

static inline int extcon_unregister_notifier(struct extcon_dev *edev,
				unsigned int id, struct notifier_block *nb)
{
	return 0;
}

static inline int extcon_register_blocking_notifier(struct extcon_dev *edev,
					unsigned int id,
					struct notifier_block *nb)
{
	return 0;
}

static inline int extcon_unregister_blocking_notifier(struct extcon_dev *edev,
					unsigned int id,
					struct notifier_block *nb)
{
	return 0;
}

static inline int devm_extcon_register_notifier(struct device *dev,
				struct extcon_dev *edev, unsigned int id,
				struct notifier_block *nb)
{
	return -ENOSYS;
}

static inline  void devm_extcon_unregister_notifier(struct device *dev,
				struct extcon_dev *edev, unsigned int id,
				struct notifier_block *nb) { }

static inline struct extcon_dev *extcon_get_extcon_dev(const char *extcon_name)
{
	return ERR_PTR(-ENODEV);
}

static inline const char *extcon_get_edev_name(struct extcon_dev *edev)
{
  return NULL;
}

static inline struct extcon_dev *extcon_find_edev_by_node(struct device_node *node)
{
	return ERR_PTR(-ENODEV);
}

static inline struct extcon_dev *extcon_get_edev_by_phandle(struct device *dev,
				int index)
{
	return ERR_PTR(-ENODEV);
}


static inline int extcon_set_property(struct extcon_dev *edev, unsigned int id,
					unsigned int prop,
					union extcon_property_value prop_val)
{
	return 0;
}

static inline int extcon_set_property_sync(struct extcon_dev *edev,
					unsigned int id, unsigned int prop,
					union extcon_property_value prop_val)
{
	return 0;
}

#endif /* CONFIG_EXTCON */

/*
 * Following structure and API are deprecated. EXTCON remains the function
 * definition to prevent the build break.
 */
struct extcon_specific_cable_nb {
       struct notifier_block *user_nb;
       int cable_index;
       struct extcon_dev *edev;
       unsigned long previous_value;
};

static inline int extcon_register_interest(struct extcon_specific_cable_nb *obj,
				const char *extcon_name, const char *cable_name,
				struct notifier_block *nb)
{
	return -EINVAL;
}

static inline int extcon_unregister_interest(struct extcon_specific_cable_nb *obj)
{
	return -EINVAL;
}

static inline int extcon_get_cable_state_(struct extcon_dev *edev, unsigned int id)
{
	return extcon_get_state(edev, id);
}

static inline int extcon_set_cable_state_(struct extcon_dev *edev, unsigned int id,
				   bool cable_state)
{
	return extcon_set_state_sync(edev, id, cable_state);
}
#endif /* __LINUX_EXTCON_H__ */
