SUBDIRS = 3ds ds

all:
	@for dir in $(SUBDIRS); do $(MAKE) -C $$dir; done

clean:
	@for dir in $(SUBDIRS); do $(MAKE) clean -C $$dir; done

3ds:
	@$(MAKE) -C 3ds

ds:
	@$(MAKE) -C ds

.PHONY: $(SUBDIRS) clean
