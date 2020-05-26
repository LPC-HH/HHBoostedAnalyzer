foreach f(`ls /eos/uscms/store/user/lpcbacon/sixie/pancakes/V1p0/MC_Fall17/v1/sixie/`)
echo $f
ls /eos/uscms/store/user/lpcbacon/sixie/pancakes/V1p0/MC_Fall17/v1/sixie/${f}/*/*/*/*.root > $f.list
end
