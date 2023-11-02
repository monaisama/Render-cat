function _checkFolder(folder)
    if not os.exists(folder) then
        os.mkdir(folder)
    end
end

function kcopy(targetPath, sourceFilePath, bcheck)
    if bcheck then _checkFolder(targetPath) end
    local targetFilePath = path.join(targetPath, path.filename(sourceFilePath))
    print('cp ' .. sourceFilePath .. ' -> ' .. targetFilePath)
    os.cp(sourceFilePath, targetFilePath)
end

function kcopyFiles(targetPath, sourceFiles)
    _checkFolder(targetPath)
    for _, file in ipairs(sourceFiles) do
        kcopy(targetPath, file)
    end
end

function kbuildBaseFolder()
    return path.join('$(buildir)', '$(plat)', '$(arch)', '$(mode)')
end