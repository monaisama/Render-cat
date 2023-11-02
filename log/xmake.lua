target('klog')
    set_kind('headeronly')
    add_headerfiles('src/*.h')
    add_rules('krule.export')