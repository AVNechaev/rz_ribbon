for /f "tokens=*" %%a in ('dir "%AppData%\MetaQuotes\Terminal" /ad/b') do xcopy "c:\program files (x86)\MultiRobotGAGARIN\MultiRobotGAGARIN_v1.2.1.s.ex4" /y "%AppData%\MetaQuotes\Terminal\%%a\MQL4\Experts\"
for /f "tokens=*" %%a in ('dir "%AppData%\MetaQuotes\Terminal" /ad/b') do xcopy "c:\program files (x86)\MultiRobotGAGARIN\MultiLentaGAGARIN_v1.2.ex4" /y "%AppData%\MetaQuotes\Terminal\%%a\MQL4\Experts\"