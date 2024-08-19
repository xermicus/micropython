SECTIONS {
    .text : { KEEP(*(.text.polkavm_export)) *(.text .text.*) }
}