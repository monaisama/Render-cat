target('kfile')
    set_kind('shared')
    add_files('src/**.cpp') -- all recursion
    add_headerfiles('src/**.h')
    add_rules('krule.export', 'krule.include.log')
    add_deps('klog')