set_warnings("everything")

if is_mode('debug') then 
    add_defines('DEBUG')
    set_optimize('none')
    set_symbols('debug')
elseif is_mode('release') then 
    set_optimize('faster')
    set_strip('all')
end

includes('math', 'project-cat')
