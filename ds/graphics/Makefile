ifeq ($(strip $(DEVKITARM)),)
$(error "Please set DEVKITARM in your environment. export DEVKITARM=<path to>devkitARM")
endif

include $(DEVKITARM)/ds_rules

GRAPHICS	:=	cards .

OUT			:=	../nitrofiles/graphics

INPUTS		:= $(foreach dir,$(GRAPHICS),$(addprefix $(dir)/,$(notdir $(wildcard $(dir)/*.bmp))))

TARGETS		:= $(foreach file,$(INPUTS:.bmp=.gfx),$(addprefix $(OUT)/, $(file)))

.PHONY	:	clean all directories

all	:	$(TARGETS)

$(OUT)/%.gfx	:	%.bmp %.txt
	@echo $$(basename $@)
	@[ -d "$(@D)" ] || mkdir -p "$(@D)"
	@bmp2ds $< $@ -o $(shell cat $(word 2,$^))

$(OUT)/%.gfx	:	%.bmp
	@echo $$(basename $@)
	@[ -d "$(@D)" ] || mkdir -p "$(@D)"
	@bmp2ds $< $@

clean	:
	@echo clean ...
	@rm -rf $(TARGETS)

cards	:
	$(MAKE) -C cards