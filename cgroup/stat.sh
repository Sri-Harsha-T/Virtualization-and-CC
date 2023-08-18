cgroup=cg1

tstart=$(date +%s%N)
cstart=$(cat /sys/fs/cgroup/cpu/$cgroup/cpuacct.usage)

sleep 5

cstop=$(cat /sys/fs/cgroup/cpu/$cgroup/cpuacct.usage)
tstop=$(date +%s%N)

bc -l <<EOF
($cstop - $cstart) / ($tstop - $tstart) * 100
EOF
