let &makeprg="./build.sh"
let g:runprgarg="quickie"
let s:includedirs=""

let s:gccvers = systemlist("gcc --version | head -1 | awk '{print $NF}'")[0]
let &path=".,include,vendor/include,".s:includedirs."/usr/lib/gcc/x86_64-pc-linux-gnu/".s:gccvers."/include,/usr/include,,"
