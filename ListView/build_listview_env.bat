:设置拉取的sdk的具体版本，默认为最新版

set sdk_ver=HEAD

if "%1" == "2003" (set sdk_vs_ver=2003) else (set sdk_vs_ver=2008)

set sdk_dev_ver=dev

set sdk_url=https://github.com/lurenpluto/BOLT_SDK/trunk

set sdk_vs_url=%sdk_url%/boltsdk_%sdk_vs_ver%

set svn_tool=..\tools\svn\svn.exe

set local_dir=..\ListView

set sdk_inc_url=%sdk_vs_url%/include

set sdk_inc=%local_dir%\include

mkdir %sdk_inc%

%svn_tool% export --force -r %sdk_ver% %sdk_inc_url% %sdk_inc%

set sdk_lib_url=%sdk_vs_url%/dev/%sdk_dev_ver%/lib

set sdk_lib=%local_dir%\lib

mkdir %sdk_lib%

%svn_tool% export --force -r %sdk_ver% %sdk_lib_url% %sdk_lib%

set sdk_xml_lib_url=%sdk_vs_url%/dev/pr/lib/libexpat.lib

%svn_tool% export --force -r %sdk_ver% %sdk_xml_lib_url% %sdk_lib%

set sdk_bin_url=%sdk_vs_url%/dev/%sdk_dev_ver%/bin

set sdk_bin=%local_dir%\bin

mkdir %sdk_bin%

%svn_tool% export --force -r %sdk_ver% %sdk_bin_url% %sdk_bin%

set sdk_dll_url=%sdk_vs_url%/bin

%svn_tool% export --depth infinity --force -r %sdk_ver% %sdk_dll_url% %sdk_bin%

set sdk_bin_url=%sdk_vs_url%/dev/%sdk_dev_ver%/bin

pause