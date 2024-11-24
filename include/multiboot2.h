#include <stdint.h>

// https://www.gnu.org/software/grub/manual/multiboot2/multiboot.html#Boot-information

typedef struct multiboot2_info_t {
    uint32_t total_size;    // contains the total size of boot information including this field and terminating tag in bytes
    uint32_t reserved;      // is always set to zero and must be ignored by OS image 
} __attribute__((packed));

typedef struct multiboot2_tag_t {
    uint32_t type;          // Contains an identifier of contents of the rest of the tag.
    uint32_t size;
    /**
     * Contains the size of tag including header fields 
     * but not including padding. 
     * Tags follow one another padded when necessary in order 
     * for each tag to start at 8-bytes aligned address. 
     * Tags are terminated by a tag of type ‘0’ and size ‘8’. 
     */
} __attribute__((packed));

typedef struct multiboot2_mem_info_t
{
    uint32_t type;
    uint32_t size;
    uint32_t mem_lower;
    uint32_t mem_upper;
} __attribute__((packed));

typedef struct multiboot2_cmd_line {
    uint32_t type;
    uint32_t sizew;

}  __attribute__((packed));

