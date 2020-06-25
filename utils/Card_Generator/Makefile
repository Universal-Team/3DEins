#---------------------------------------------------------------------------------
.SUFFIXES:
#---------------------------------------------------------------------------------

ifeq ($(strip $(DEVKITARM)),)
$(error "Please set DEVKITARM in your environment. export DEVKITARM=<path to>devkitARM")
endif

TOPDIR ?= $(CURDIR)
include $(DEVKITARM)/3ds_rules

#---------------------------------------------------------------------------------
TARGET		:=	$(notdir $(CURDIR))
GRAPHICS	:=	gfx
GFXBUILD	:=	out

#---------------------------------------------------------------------------------
# no real need to edit anything past this point unless you need to add additional
# rules for different file extensions
#---------------------------------------------------------------------------------
ifneq ($(BUILD),$(notdir $(CURDIR)))
#---------------------------------------------------------------------------------

export OUTPUT	:=	$(CURDIR)/$(TARGET)
export TOPDIR	:=	$(CURDIR)

export VPATH	:=	$(foreach dir,$(GRAPHICS),$(CURDIR)/$(dir))

export DEPSDIR	:=	$(CURDIR)/$(BUILD)
GFXFILES	:=	$(foreach dir,$(GRAPHICS),$(notdir $(wildcard $(dir)/*.t3s)))

#---------------------------------------------------------------------------------
export T3XFILES	:=	$(patsubst %.t3s, $(GFXBUILD)/%.t3x, $(GFXFILES))
#---------------------------------------------------------------------------------
.PHONY: all clean random

#---------------------------------------------------------------------------------
all: $(GFXBUILD) $(DEPSDIR) $(T3XFILES)
#---------------------------------------------------------------------------------
random:
	@g++ CardRandomizer.cpp -o CardRandomizer
	./CardRandomizer
#---------------------------------------------------------------------------------
clean:
	@echo clean ...
	@rm -fr out/cards.t3x
#---------------------------------------------------------------------------------
$(GFXBUILD)/cards.t3x:	cards.t3s
#---------------------------------------------------------------------------------
	@echo build cards SpriteSheet...
	@tex3ds -i $< -o $(GFXBUILD)/cards.t3x
	@echo Done!
	@echo Now copy the cards.t3x file over to your SD Card at "sdmc:/3ds/3DEins/sets/<SetName>/" and the Set.json file as well.


#---------------------------------------------------------------------------------
.PRECIOUS	:	%.t3x
#---------------------------------------------------------------------------------
%.t3x:	%.t3s
#---------------------------------------------------------------------------------
	@echo $(notdir $<)
	@tex3ds -i $< -o $*.t3x

#---------------------------------------------------------------------------------------
endif
#---------------------------------------------------------------------------------------
