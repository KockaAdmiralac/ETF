sudo /var/www/html/jobe/application/libraries/../../runguard/runguard --user=jobe00 --group=jobe --time=5 --filesize=20000 --nproc=21 --no-core --streamsize=2000 --memsize=400000 sh -c '/usr/bin/python3 -BE prog.python3' >prog.out 2>prog.err <prog.in
