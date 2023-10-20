add_requires('glew', 'glfw', {configs = {shared = true}})

target('project-cat')
    set_kind('binary')
    add_files('src/*.cpp')
    add_packages('glew', 'glfw')
    add_deps('kmath')
    add_includedirs('../math/src')