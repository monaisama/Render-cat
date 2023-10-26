rule('shader')
    set_extensions('.fs', '.vs', '.glsl')
    on_build_files(function(target, filepatch, opt)
        local targetPath = path.join('$(buildir)', '$(plat)', '$(arch)', '$(mode)')
        for _, file in ipairs(filepatch.sourcefiles) do 
            local targetFilePath = path.join(targetPath, path.filename(file))
            print('cp ' .. file .. ' -> ' .. targetFilePath)
            os.cp(file, targetFilePath)
        end 
    end)
rule_end()

target('shader')
    set_kind('object')
    add_rules('shader')
    add_files('**.fs', '**.vs')