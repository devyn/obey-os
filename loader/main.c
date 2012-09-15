#include "multiboot.h"

#include "main.h"
#include "../output/output.h"

void os_main (multiboot_uint32_t magic, multiboot_info_t *mbi) {

	output_clear ();
	output_write ("Starting OS...\n");

	if (!mbi || magic != MULTIBOOT_BOOTLOADER_MAGIC) {
		/**
		 * Something did not go according to specs.
		 * Print an error message and halt, but do not
		 * rely on the multiboot data structure.
		 **/
		output_printf ("Multiboot magic incorrect (got 0x%x!\n", (int) magic);
		return;
	}

	output_printf ("Flags: %b\n", (int) mbi->flags);

	if (mbi->flags & MULTIBOOT_INFO_MEMORY) {
		/* The mbi->mem_* members are set. */
		output_printf ("mem_lower = %d KB, mem_upper = %d KB\n", (int) mbi->mem_lower, (int) mbi->mem_upper);
	}

	if (mbi->flags & MULTIBOOT_INFO_BOOTDEV) {
		/* The mbi->boot_device member is set. */
		output_printf ("boot_device = 0x%x\n", (int) mbi->boot_device);
	}

	if (mbi->flags & MULTIBOOT_INFO_CMDLINE) {
		/* The mbi->cmdline member is set. */
		output_printf ("cmdline = \"%s\"\n", (char *) mbi->cmdline);

	}

	if (mbi->flags & MULTIBOOT_INFO_MODS) {
		/* The mbi->mods_* members are set. */
		multiboot_module_t *mod = (multiboot_module_t*) mbi->mods_addr;

		output_printf ("mods_count = %d, mods_addr = 0x%x\n", (int) mbi->mods_count, (int) mbi->mods_addr);
		for (int i = 0; i < (int) mbi->mods_count; i++, mod++) {
			output_printf (
				" %d) mod_start = 0x%x, mod_end = 0x%x, cmdline = %s\n",
				i + 1, (int) mod->mod_start, (int) mod->mod_end, (char *) mod->cmdline);
		}
	}

	if ((mbi->flags & MULTIBOOT_INFO_AOUT_SYMS) && (mbi->flags & MULTIBOOT_INFO_ELF_SHDR)) {
		/* These should be mutually exclusive! */
		output_write ("Bits 4 and 5 are supposed to be mutually exclusive!\n");
		return;
	}

	if (mbi->flags & MULTIBOOT_INFO_AOUT_SYMS) {
		/* The a.out symbol table is loaded. */
		multiboot_aout_symbol_table_t *multiboot_aout_sym = &mbi->u.aout_sym;

		output_printf ("multiboot_aout_symbol_table: tabsize = 0x%0x, strsize = 0x%x, addr = 0x%x\n",
			(int) multiboot_aout_sym->tabsize,
			(int) multiboot_aout_sym->strsize,
			(int) multiboot_aout_sym->addr);

	} else if (mbi->flags & MULTIBOOT_INFO_ELF_SHDR) {
		/* The ELF section header table is loaded. */
		multiboot_elf_section_header_table_t *multiboot_elf_sec = &mbi->u.elf_sec;

		output_printf ("multiboot_elf_sec: num = %u, size = 0x%x, addr = 0x%x, shndx = 0x%x\n",
			(int) multiboot_elf_sec->num, (int) multiboot_elf_sec->size,
			(int) multiboot_elf_sec->addr, (int) multiboot_elf_sec->shndx);

	}

	if (mbi->flags & MULTIBOOT_INFO_MEM_MAP) {
		/* The mbi->mmap_* members are set. */
		multiboot_memory_map_t *mmap;

		output_printf ("mmap_addr = 0x%x, mmap_length = 0x%x\n",
			(int) mbi->mmap_addr, (int) mbi->mmap_length);

		for (mmap = (multiboot_memory_map_t *) mbi->mmap_addr;
			(unsigned long) mmap < mbi->mmap_addr + mbi->mmap_length;
			mmap = (multiboot_memory_map_t *) ((unsigned long) mmap + mmap->size + sizeof (mmap->size))) {

			output_printf (" - size = 0x%x, base_addr = 0x%x%x, length = 0x%x%x, type = 0x%x\n",
				(int) mmap->size,
				mmap->addr >> 32,
				mmap->addr & 0xffffffff,
				mmap->len >> 32,
				mmap->len & 0xffffffff,
				(int) mmap->type);
		}
	}

	if (mbi->flags & MULTIBOOT_INFO_DRIVE_INFO) {
		/* The mbi->drives_* members are set. */
	}

	if (mbi->flags & MULTIBOOT_INFO_CONFIG_TABLE) {
		/* The mbi->config_table member is set. */
	}

	if (mbi->flags & MULTIBOOT_INFO_BOOT_LOADER_NAME) {
		/* The mbi->boot_loader_name member is set. */
		output_printf ("The bootloader was \"%s\"\n", (char *) mbi->boot_loader_name);
	}

	if (mbi->flags & MULTIBOOT_INFO_APM_TABLE) {
		/* The mbi->apm_table member is set. */
	}

	if (mbi->flags & MULTIBOOT_INFO_VIDEO_INFO) {
		/* The mbi->vbe_* members are set. */
	}

	output_write ("Halting.\n");

}


#ifdef TESTS_ENABLED

#include <stdio.h>

int main(void) {
	puts ("There are no tests to run here.");
	return 0;
}

#endif
