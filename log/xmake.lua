target('klog')
    set_kind('shared')
    add_files('src/*.cpp')
    add_headerfiles('src/*.h')
    add_rules('krule.export')