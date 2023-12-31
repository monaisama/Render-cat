set_warnings('everything') -- , 'error')
set_languages('cxx20')

-- common includes
add_includedirs('common/src/')

rule('kmode.debug')
    on_load(function(target)
        if is_mode('debug') then 
            target:add('defines', 'KDEBUG')
            target:set('optimize', 'none')
            target:set('symbols', 'debug')
        end 
    end)
rule_end()

rule('kmode.release')
    on_load(function(target)
        if is_mode('release') then 
            target:set('optimize', 'faster')
            target:set('strip', 'all')
        end
    end)
rule_end()

rule('krule.export')
    on_load(function(target)
        target:add('defines', 'KEXPORT')
    end)
rule_end()

rule('krule.include.math')
    on_load(function(target)
        target:add('includedirs', 'math/src')
    end)
rule_end()

rule('krule.include.log')
    on_load(function(target)
        target:add('includedirs', 'log/src')
    end)
rule_end()

rule('krule.include.file')
    on_load(function(target)
        target:add('includedirs', 'file/src')
    end)
rule_end()

rule('krule.include.self')
    on_load(function(target)
        local includePath = path.join(target:scriptdir(), 'src')
        if os.exists(includePath) then 
            target:add('includedirs', path.join(target:scriptdir(), 'src'))
        end 
    end)
rule_end()

add_rules('krule.include.self')
add_rules('kmode.debug', 'kmode.release')
includes('math', 'project-cat', 'file', 'log', 'physics')
-- includes('resource') -- 不再拷贝，直接使用项目路径
includes('test')
