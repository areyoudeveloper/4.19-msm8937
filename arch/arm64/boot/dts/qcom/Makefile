# SPDX-License-Identifier: GPL-2.0
dtb-$(CONFIG_ARCH_QCOM)	+= apq8016-sbc.dtb
dtb-$(CONFIG_ARCH_QCOM)	+= apq8096-db820c.dtb
dtb-$(CONFIG_ARCH_QCOM)	+= ipq8074-hk01.dtb
dtb-$(CONFIG_ARCH_QCOM)	+= msm8916-mtp.dtb
dtb-$(CONFIG_ARCH_QCOM)	+= msm8992-bullhead-rev-101.dtb
dtb-$(CONFIG_ARCH_QCOM)	+= msm8994-angler-rev-101.dtb
dtb-$(CONFIG_ARCH_QCOM)	+= msm8996-mtp.dtb
dtb-$(CONFIG_ARCH_QCOM)	+= sdm845-mtp.dtb
ifeq ($(CONFIG_MACH_XIAOMI_MSM8937),y)
dtb-$(CONFIG_MACH_XIAOMI_LAND) += msm8937-pmi8950-qrd-sku1-land.dtb
else
dtb-$(CONFIG_ARCH_MSM8937) += msm8937-pmi8950-mtp.dtb \
	msm8937-interposer-sdm439-cdp.dtb \
	msm8937-interposer-sdm439-mtp.dtb \
	msm8937-interposer-sdm439-qrd.dtb \
	msm8937-interposer-sdm429-cdp.dtb \
	msm8937-interposer-sdm429-mtp.dtb
endif

always		:= $(dtb-y)
subdir-y	:= $(dts-dirs)
clean-files    := *.dtb *.dtbo
