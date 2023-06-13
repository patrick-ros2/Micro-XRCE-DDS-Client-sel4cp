SHELL = /bin/zsh
PWD_DIR = "$(shell basename $$(pwd))"
BUILD_DIR = build

# ==================================
# Pushes the current directory to remote host.
# ==================================

NUM_PROCS = 4
REMOTE_USER_HOST = "patrick@vm_comp4961_ubuntu2204"
REMOTE_DEST_DIR = "~/remote/$(shell hostname -s)/"

.PHONY: push-remote
push-remote:
	# Make the directory on the remote if it doesn't exist already.
	(ssh -t $(REMOTE_USER_HOST) "mkdir -p $(REMOTE_DEST_DIR)$(PWD_DIR)")
	# Sync our current directory with the remote.
	(rsync -a \
 			--delete \
 			--exclude "build" \
 			--exclude "build-remote" \
 			--exclude "cmake-build*" \
 			--exclude ".vscode" \
 			--exclude ".idea" \
 			--exclude ".git" \
 			--exclude ".gitignore" \
 			./ $(REMOTE_USER_HOST):$(REMOTE_DEST_DIR)$(PWD_DIR))

# ==================================
# Runs a Make command remotely.
# ==================================

.PHONY: remote
remote: push-remote
	ssh -t $(REMOTE_USER_HOST) "\
		cd $(REMOTE_DEST_DIR)$(PWD_DIR) ; \
		zsh -ilc 'make $(MAKE_CMD)' ; "

# ==================================
# Clean
# ==================================

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)

# ==================================
# Build
# ==================================

.PHONY: build
build:
	CC=aarch64-none-elf-gcc CXX=aarch64-none-elf-g++ \
		cmake -S . -B $(BUILD_DIR) \
			-DCMAKE_C_COMPILER_WORKS=1 \
			-DCMAKE_CXX_COMPILER_WORKS=1 \
			-DUCLIENT_SUPERBUILD=0 \
			-DCMAKE_SYSTEM_NAME="Generic" \
			-DPLATFORM_NAME="LwIP" \
			-DUCLIENT_PROFILE_SERIAL=0 \
			-DUCLIENT_PROFILE_TCP=0 \
			-DUCLIENT_PROFILE_UDP=0 \
			-DUCLIENT_PROFILE_DISCOVERY=0
	cd $(BUILD_DIR) && $(MAKE) -j $(NUM_PROCS)
