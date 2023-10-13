target('kmath')
    set_kind('shared')
    add_files('src/*.cpp')

    if is_mode('debug') then
        set_optimize('none')
        set_symbols('debug')
    elseif is_mode('release') then 
        set_strip('all')
        set_optimize('faster')
    end 