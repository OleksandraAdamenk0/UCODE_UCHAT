MAKEFLAGS += --no-print-directory
CC = clang
FLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic

# CLIENT
CNTDIR = client
CLIENT = uchat

# SERVER
SVRDIR = server
SERVER = uchat_server

all: $(SVRDIR)/(SERVER) $(CNTDIR)/$(CLIENT)
	@mv $(CNTDIR)/$(CLIENT) .
	@mv $(SVRDIR)/$(SERVER) .

$(SVRDIR)/(SERVER):
	@$(MAKE) -C $(SVRDIR)

$(CNTDIR)/$(CLIENT):
	@$(MAKE) -C $(CNTDIR)

clean:
	@$(MAKE) clean -C $(CNTDIR)
	@$(MAKE) clean -C $(SVRDIR)

uninstall: clean
	@$(MAKE) uninstall -C $(CNTDIR)
	@$(MAKE) uninstall -C $(SVRDIR)
	@if [ -f $(CLIENT) ]; then rm $(CLIENT); fi
	@if [ -f $(SERVER) ]; then rm $(SERVER); fi

reinstall: uninstall all

.PHONY: all clean uninstall reinstall
