add_requires('glew', 'glfw', {configs = {shared = true}})

target('project-cat')
    set_kind('binary')
    add_files('src/**.cpp')
    add_headerfiles('src/**.h')
    add_packages('glew', 'glfw')
    add_deps('kmath', 'kfile', 'klog')
    add_rules('krule.include.math', 'krule.include.log', 'krule.include.file')