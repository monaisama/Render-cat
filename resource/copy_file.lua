function kcopy(targetPath, sourceFilePath)
    local targetFilePath = path.join(targetPath, path.filename(sourceFilePath))
    print('cp ' .. sourceFilePath .. ' -> ' .. targetFilePath)
    os.cp(sourceFilePath, targetFilePath)
end

function kcopyFiles(targetPath, sourceFiles)
    if not os.exists(targetPath) then
        os.mkdir(targetPath)
    end
    for _, file in ipairs(sourceFiles) do
        kcopy(targetPath, file)
    end
end

function kbuildBaseFolder()
    return path.join('$(buildir)', '$(plat)', '$(arch)', '$(mode)')
end