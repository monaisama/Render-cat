add_requires('glew', 'glfw', {configs = {shared = true}})

target('hello')
    set_kind('binary')
    add_files('src/*.cpp')
    add_packages('glew', 'glfw')
    add_deps('kmath')
    add_includedirs('../math/src')

    if is_mode('debug') then
        add_defines('DEBUG')
        set_symbols('debug')
        set_optimize('none')
    elseif is_mode('release') then
        set_strip('all')
        set_optimize('faster')
    end