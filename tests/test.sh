#!/bin/sh

if [ ! -e "42sh" ]; then
    echo "42sh: No such file or directory"
    exit 1
else
    echo Test 1 :
    ./42sh -c "echo yes; if true; then true; else false; fi" | tr ' ' '\n' > file1
    val1=$?
    bash --posix -c "echo yes; if true; then true; else false; fi" | tr ' ' '\n' > file2
    val2=$?
    diff -u file1 file2
    res=$?
    if [ $res -eq 0 ]; then
        echo "Assert ok"
        echo ""
    else
        echo "Test failed"
        echo ""
    fi
    if [ $val1 -ne $val2 ]; then
        echo --- ERROR RETURN VALUE ---
        echo expected $val2 but got $val1
    fi

    echo Test 2 :
    ./42sh -c "echo test redirection > file1.txt" | tr ' ' '\n' > file1
    val1=$?
    bash --posix -c "echo test redirection > file2.txt" | tr ' ' '\n' > file2
    val2=$?
    diff -u file1 file2
    res=$?
    if [ $res -eq 0 ]; then
        echo "Assert 1 ok"
        echo ""
    else
        echo "Test 1 failed"
        echo ""
    fi
    diff -u file1.txt file2.txt
    res=$?
    if [ $res -eq 0 ]; then
        echo "Assert 2 ok"
        echo ""
    else
        echo "Test 2 failed"
        echo ""
    fi
    if [ $val1 -ne $val2 ]; then
        echo --- ERROR RETURN VALUE --- 
        echo expected $val2 but got $val1
    fi

    echo Test 3 :
    ./42sh -c "if if true; then true; else false; fi; then echo true; else echo false; fi" | tr ' ' '\n' > file1
    val1=$?
    bash --posix -c "if if true; then true; else false; fi; then echo true; else echo false; fi" | tr ' ' '\n' > file2
    val2=$?
    diff -u file1 file2
    res=$?
    if [ $res -eq 0 ]; then
        echo "Assert ok"
        echo ""
    else
        echo "Test failed"
        echo ""
    fi
    if [ $val1 -ne $val2 ]; then
        echo --- ERROR RETURN VALUE --- 
        echo expected $val2 but got $val1
    fi

    echo Test 4 :
    ./42sh -c "if true; then if true; then echo true; else echo false; fi; else echo second; fi" | tr ' ' '\n' > file1
    val1=$?
    bash --posix -c "if true; then if true; then echo true; else echo false; fi; else echo second; fi" | tr ' ' '\n' > file2
    val2=$?
    diff -u file1 file2
    res=$?
    if [ $res -eq 0 ]; then
        echo "Assert ok"
        echo ""
    else
        echo "Test failed"
        echo ""
    fi
    if [ $val1 -ne $val2 ]; then
        echo --- ERROR RETURN VALUE --- 
        echo expected $val2 but got $val1
    fi

    echo Test 5 :
    ./42sh -c "if true; then if false; then echo true; else echo false; fi; else echo second; fi" | tr ' ' '\n' > file1
    val1=$?
    bash --posix -c "if true; then if false; then echo true; else echo false; fi; else echo second; fi" | tr ' ' '\n' > file2
    val2=$?
    diff -u file1 file2
    res=$?
    if [ $res -eq 0 ]; then
        echo "Assert ok"
        echo ""
    else
        echo "Test failed"
        echo ""
    fi
    if [ $val1 -ne $val2 ]; then
        echo --- ERROR RETURN VALUE --- 
        echo expected $val2 but got $val1
    fi

    echo Test 6 :
    ./42sh -c "echo test" | tr ' ' '\n' > file1
    val1=$?
    bash --posix -c "echo test" | tr ' ' '\n' > file2
    val2=$?
    diff -u file1 file2
    res=$?
    if [ $res -eq 0 ]; then
        echo "Assert ok"
        echo ""
    else
        echo "Test failed"
        echo ""
    fi
    if [ $val1 -ne $val2 ]; then
        echo --- ERROR RETURN VALUE --- 
        echo expected $val2 but got $val1
    fi

    echo Test 7 :
    ./42sh -c "echo test;" | tr ' ' '\n' > file1
    val1=$?
    bash --posix -c "echo test;" | tr ' ' '\n' > file2
    val2=$?
    diff -u file1 file2
    res=$?
    if [ $res -eq 0 ]; then
        echo "Assert ok"
        echo ""
    else
        echo "Test failed"
        echo ""
    fi
    if [ $val1 -ne $val2 ]; then
        echo --- ERROR RETURN VALUE --- 
        echo expected $val2 but got $val1
    fi

    echo Test 8 :
    ./42sh -c "echo yes; if true; then true; else false; fi" | tr ' ' '\n' > file1
    val1=$?
    bash --posix -c "echo yes; if true; then true; else false; fi" | tr ' ' '\n' > file2
    val2=$?
    diff -u file1 file2
    res=$?
    if [ $res -eq 0 ]; then
        echo "Assert ok"
        echo ""
    else
        echo "Test failed"
        echo ""
    fi
    if [ $val1 -ne $val2 ]; then
        echo --- ERROR RETURN VALUE --- 
        echo expected $val2 but got $val1
    fi

    echo Test 9 :
    ./42sh -c "echo yes; if true; then true; else false; fi" | tr ' ' '\n' > file1
    val1=$?
    bash --posix -c "echo yes; if true; then true; else false; fi" | tr ' ' '\n' > file2
    val2=$?
    diff -u file1 file2
    res=$?
    if [ $res -eq 0 ]; then
        echo "Assert ok"
        echo ""
    else
        echo "Test failed"
        echo ""
    fi
    if [ $val1 -ne $val2 ]; then
        echo --- ERROR RETURN VALUE --- 
        echo expected $val2 but got $val1
    fi

    echo Test 10 :
    ./42sh -c "echo test redirection 2> file1.txt" | tr ' ' '\n' > file1
    val1=$?
    bash --posix -c "echo test redirection 2> file2.txt" | tr ' ' '\n' > file2
    val2=$?
    diff -u file1 file2
    res=$?
    if [ $res -eq 0 ]; then
        echo "Assert 1 ok"
        echo ""
    else
        echo "Test 1 failed"
        echo ""
    fi
    diff -u file1.txt file2.txt
    res=$?
    if [ $res -eq 0 ]; then
        echo "Assert 2 ok"
        echo ""
    else
        echo "Test 2 failed"
        echo ""
    fi
    if [ $val1 -ne $val2 ]; then
        echo --- ERROR RETURN VALUE --- 
        echo expected $val2 but got $val1
    fi

    echo Test 11 :
    ./42sh -c "echo test redirection > file1.txt" | tr ' ' '\n' > file1
    val1=$?
    bash --posix -c "echo test redirection > file2.txt" | tr ' ' '\n' > file2
    val2=$?
    diff -u file1 file2
    res=$?
    if [ $res -eq 0 ]; then
        echo "Assert 1 ok"
        echo ""
    else
        echo "Test 1 failed"
        echo ""
    fi
    diff -u file1.txt file2.txt
    res=$?
    if [ $res -eq 0 ]; then
        echo "Assert 2 ok"
        echo ""
    else
        echo "Test 2 failed"
        echo ""
    fi
    if [ $val1 -ne $val2 ]; then
        echo --- ERROR RETURN VALUE --- 
        echo expected $val2 but got $val1
    fi

    echo Test 12 :
    ./42sh -c "cat < file1.txt" | tr ' ' '\n' > file1
    val1=$?
    bash --posix -c "cat < file1.txt" | tr ' ' '\n' > file2
    val2=$?
    diff -u file1 file2
    res=$?
    if [ $res -eq 0 ]; then
        echo "Assert 1 ok"
        echo ""
    else
        echo "Test 1 failed"
        echo ""
    fi
    diff -u file1.txt file2.txt
    res=$?
    if [ $res -eq 0 ]; then
        echo "Assert 2 ok"
        echo ""
    else
        echo "Test 2 failed"
        echo ""
    fi
    if [ $val1 -ne $val2 ]; then
        echo --- ERROR RETURN VALUE --- 
        echo expected $val2 but got $val1
    fi

    echo Test 13 :
    ./42sh -c "echo test redirection > file1.txt 2>&1" | tr ' ' '\n' > file1
    val1=$?
    bash --posix -c "echo test redirection > file2.txt 2>&1" | tr ' ' '\n' > file2
    val2=$?
    diff -u file1 file2
    res=$?
    if [ $res -eq 0 ]; then
        echo "Assert 1 ok"
        echo ""
    else
        echo "Test 1 failed"
        echo ""
    fi
    diff -u file1.txt file2.txt
    res=$?
    if [ $res -eq 0 ]; then
        echo "Assert 2 ok"
        echo ""
    else
        echo "Test 2 failed"
        echo ""
    fi
    if [ $val1 -ne $val2 ]; then
        echo --- ERROR RETURN VALUE --- 
        echo expected $val2 but got $val1
    fi

    echo Test 14 :
    ./42sh -c "echo wesh la zone" | tr ' ' '\n' > file1
    val1=$?
    bash --posix -c "echo wesh la zone" | tr ' ' '\n' > file2
    val2=$?
    diff -u file1 file2
    res=$?
    if [ $res -eq 0 ]; then
        echo "Assert ok"
        echo ""
    else
        echo "Test failed"
        echo ""
    fi
    if [ $val1 -ne $val2 ]; then
        echo --- ERROR RETURN VALUE --- 
        echo expected $val2 but got $val1
    fi

    echo Test 15 :
    ./42sh -c "echo coucou les loulou; echo bonsoir;" | tr ' ' '\n' > file1
    val1=$?
    bash --posix -c "echo coucou les loulou; echo bonsoir;" | tr ' ' '\n' > file2
    val2=$?
    diff -u file1 file2
    res=$?
    if [ $res -eq 0 ]; then
        echo "Assert ok"
        echo ""
    else
        echo "Test failed"
        echo ""
    fi
    if [ $val1 -ne $val2 ]; then
        echo --- ERROR RETURN VALUE --- 
        echo expected $val2 but got $val1
    fi

    echo Test 16 :
    ./42sh -c "if true; then echo alright; else echo no; fi" | tr ' ' '\n' > file1
    val1=$?
    bash --posix -c "if true; then echo alright; else echo no; fi" | tr ' ' '\n' > file2
    val2=$?
    diff -u file1 file2
    res=$?
    if [ $res -eq 0 ]; then
        echo "Assert ok"
        echo ""
    else
        echo "Test failed"
        echo ""
    fi
    if [ $val1 -ne $val2 ]; then
        echo --- ERROR RETURN VALUE --- 
        echo expected $val2 but got $val1
    fi

    echo Test 17 :
    ./42sh -c "if true; then echo no; else echo yes; fi" | tr ' ' '\n' > file1
    val1=$?
    bash --posix -c "if true; then echo no; else echo yes; fi" | tr ' ' '\n' > file2
    val2=$?
    diff -u file1 file2
    res=$?
    if [ $res -eq 0 ]; then
        echo "Assert ok"
        echo ""
    else
        echo "Test failed"
        echo ""
    fi
    if [ $val1 -ne $val2 ]; then
        echo --- ERROR RETURN VALUE --- 
        echo expected $val2 but got $val1
    fi

    echo Test 18 :
    ./42sh -c "if false; then echo not printed; else echo guten tag; fi" | tr ' ' '\n' > file1
    val1=$?
    bash --posix -c "if false; then echo not printed; else echo guten tag; fi" | tr ' ' '\n' > file2
    val2=$?
    diff -u file1 file2
    res=$?
    if [ $res -eq 0 ]; then
        echo "Assert ok"
        echo ""
    else
        echo "Test failed"
        echo ""
    fi
    if [ $val1 -ne $val2 ]; then
        echo --- ERROR RETURN VALUE --- 
        echo expected $val2 but got $val1
    fi

    echo Test 19 :
    ./42sh -c "echo Bonsoir les amigos | tr o Z" | tr ' ' '\n' > file1
    val1=$?
    bash --posix -c "echo Bonsoir les amigos | tr o Z" | tr ' ' '\n' > file2
    val2=$?
    diff -u file1 file2
    res=$?
    if [ $res -eq 0 ]; then
        echo "Assert ok"
        echo ""
    else
        echo "Test failed"
        echo ""
    fi
    if [ $val1 -ne $val2 ]; then
        echo --- ERROR RETURN VALUE --- 
        echo expected $val2 but got $val1
    fi

    echo Test 20 :
    ./42sh -c "echo Bonsoir les amigos && echo echo" | tr ' ' '\n' > file1
    val1=$?
    bash --posix -c "echo Bonsoir les amigos && echo echo" | tr ' ' '\n' > file2
    val2=$?
    diff -u file1 file2
    res=$?
    if [ $res -eq 0 ]; then
        echo "Assert ok"
        echo ""
    else
        echo "Test failed"
        echo ""
    fi
    if [ $val1 -ne $val2 ]; then
        echo --- ERROR RETURN VALUE --- 
        echo expected $val2 but got $val1
    fi

    echo Test 21 :
    ./42sh -c "echo fi do done else && echo" | tr ' ' '\n' > file1
    val1=$?
    bash --posix -c "echo fi do done else && echo" | tr ' ' '\n' > file2
    val2=$?
    diff -u file1 file2
    res=$?
    if [ $res -eq 0 ]; then
        echo "Assert ok"
        echo ""
    else
        echo "Test failed"
        echo ""
    fi
    if [ $val1 -ne $val2 ]; then
        echo --- ERROR RETURN VALUE --- 
        echo expected $val2 but got $val1
    fi

    echo Test 22 :
    ./42sh -c "echo fi do || echo no; if true; then echo true; else echo false; fi" | tr ' ' '\n' > file1
    val1=$?
    bash --posix -c "echo fi do || echo no; if true; then echo true; else echo false; fi" | tr ' ' '\n' > file2
    val2=$?
    diff -u file1 file2
    res=$?
    if [ $res -eq 0 ]; then
        echo "Assert ok"
        echo ""
    else
        echo "Test failed"
        echo ""
    fi
    if [ $val1 -ne $val2 ]; then
        echo --- ERROR RETURN VALUE --- 
        echo expected $val2 but got $val1
    fi


    echo Test 31 :
    ./42sh -c "if true; then true; else false; fi" | tr ' ' '\n' > file1
    val1=$?
    bash --posix -c "if true; then true; else false; fi" | tr ' ' '\n' > file2
    val2=$?
    diff -u file1 file2
    res=$?
    if [ $res -eq 0 ]; then
        echo "Assert ok"
        echo ""
    else
        echo "Test failed"
        echo ""
    fi
    if [ $val1 -ne $val2 ]; then
        echo --- ERROR RETURN VALUE --- 
        echo expected $val2 but got $val1
    fi

    echo Test 32 :
    ./42sh -c "if true; then true else false; fi" | tr ' ' '\n' > file1
    val1=$?
    bash --posix -c "if true; then true else false; fi" | tr ' ' '\n' > file2
    val2=$?
    diff -u file1 file2
    res=$?
    if [ $res -eq 0 ]; then
        echo "Assert ok"
        echo ""
    else
        echo "Test failed"
        echo ""
    fi
    if [ $val1 -ne $val2 ]; then
        echo --- ERROR RETURN VALUE --- 
        echo expected $val2 but got $val1
    fi

    echo Test 33 :
    ./42sh -c "echo 'lou'" | tr ' ' '\n' > file1
    val1=$?
    bash --posix -c "echo 'lou'" | tr ' ' '\n' > file2
    val2=$?
    diff -u file1 file2
    res=$?
    if [ $res -eq 0 ]; then
        echo "Assert ok"
        echo ""
    else
        echo "Test failed"
        echo ""
    fi
    if [ $val1 -ne $val2 ]; then
        echo --- ERROR RETURN VALUE ---
        echo expected $val2 but got $val1
    fi

    echo Test 34 :
    ./42sh -c "echo 'lou'\'a" > file1
    val1=$?
    bash --posix -c "echo 'lou'\'a" > file2
    val2=$?
    diff -u file1 file2
    res=$?
    if [ $res -eq 0 ]; then
        echo "Assert ok"
        echo ""
    else
        echo "Test failed"
        echo ""
    fi
    if [ $val1 -ne $val2 ]; then
        echo --- ERROR RETURN VALUE --- 
        echo expected $val2 but got $val1
    fi



    echo Test 35 :
    ./42sh -c "echo lou\'" | tr ' ' '\n' > file1
    val1=$?
    bash --posix -c "echo lou\'" | tr ' ' '\n' > file2
    val2=$?
    diff -u file1 file2
    res=$?
    if [ $res -eq 0 ]; then
        echo "Assert ok"
        echo ""
    else
        echo "Test failed"
        echo ""
    fi
    if [ $val1 -ne $val2 ]; then
        echo --- ERROR RETURN VALUE --- 
        echo expected $val2 but got $val1
    fi

    echo Test 36 :
    ./42sh -c "echo -e bjr' la zone'\'" > file1
    val1=$?
    bash --posix -c "echo -e bjr' la zone'\'" > file2
    val2=$?
    diff -u file1 file2
    res=$?
    if [ $res -eq 0 ]; then
        echo "Assert ok"
        echo ""
    else
        echo "Test failed"
        echo ""
    fi
    if [ $val1 -ne $val2 ]; then
        echo --- ERROR RETURN VALUE ---
        echo expected $val2 but got $val1
    fi

    echo Test 37 :
    ./42sh -c "echo -n lou\'" | tr ' ' '\n' > file1
    val1=$?
    bash --posix -c "echo -n lou\'" | tr ' ' '\n' > file2
    val2=$?
    diff -u file1 file2
    res=$?
    if [ $res -eq 0 ]; then
        echo "Assert ok"
        echo ""
    else
        echo "Test failed"
        echo ""
    fi
    if [ $val1 -ne $val2 ]; then
        echo --- ERROR RETURN VALUE --- 
        echo expected $val2 but got $val1
    fi

    echo Test 38 :
    ./42sh -c "if true; then ls; fi" > file1
    val1=$?
    bash --posix -c "if true; then ls; fi" > file2
    val2=$?
    diff -u file1 file2
    res=$?
    if [ $res -eq 0 ]; then
        echo "Assert ok"
        echo ""
    else
        echo "Test failed"
        echo ""
    fi
    if [ $val1 -ne $val2 ]; then
        echo --- ERROR RETURN VALUE --- 
        echo expected $val2 but got $val1
    fi

    echo Test 39 :
    ./42sh -c "if true; then ls; fi; echo ok" > file1
    val1=$?
    bash --posix -c "if true; then ls; fi; echo ok" > file2
    val2=$?
    diff -u file1 file2
    res=$?
    if [ $res -eq 0 ]; then
        echo "Assert ok"
        echo ""
    else
        echo "Test failed"
        echo ""
    fi
    if [ $val1 -ne $val2 ]; then
        echo --- ERROR RETURN VALUE ---
        echo expected $val2 but got $val1
    fi

    echo Test 40 :
    ./42sh -c "if false; then ls; fi; echo ok;" > file1
    val1=$?
    bash --posix -c "if false; then ls; fi; echo ok;" > file2
    val2=$?
    diff -u file1 file2
    res=$?
    if [ $res -eq 0 ]; then
        echo "Assert ok"
        echo ""
    else
        echo "Test failed"
        echo ""
    fi
    if [ $val1 -ne $val2 ]; then
        echo --- ERROR RETURN VALUE ---
        echo expected $val2 but got $val1
    fi

    echo Test 41 :
    ./42sh -c "if false; then ls; elif true; then cat Makefile; fi; echo ok;" > file1
    val1=$?
    bash --posix -c  "if false; then ls; elif true; then cat Makefile; fi; echo ok;" > file2
    val2=$?
    diff -u file1 file2
    res=$?
    if [ $res -eq 0 ]; then
        echo "Assert ok"
        echo ""
    else
        echo "Test failed"
        echo ""
    fi
    if [ $val1 -ne $val2 ]; then
        echo --- ERROR RETURN VALUE ---
        echo expected $val2 but got $val1
    fi

    echo Test 42 :
    ./42sh -c "cat Makefile; ls; echo ok; echo no;" > file1
    val1=$?
    bash --posix -c  "cat Makefile; ls; echo ok; echo no;" > file2
    val2=$?
    diff -u file1 file2
    res=$?
    if [ $res -eq 0 ]; then
        echo "Assert ok"
        echo ""
    else
        echo "Test failed"
        echo ""
    fi
    if [ $val1 -ne $val2 ]; then
        echo --- ERROR RETURN VALUE ---
        echo expected $val2 but got $val1
    fi

    echo Test 43 :
    ./42sh -c "echo -e ccyo; echo ok; echo no; echo bjr" > file1
    val1=$?
    bash --posix -c "echo -e ccyo; echo ok; echo no; echo bjr" > file2
    val2=$?
    diff -u file1 file2
    res=$?
    if [ $res -eq 0 ]; then
        echo "Assert ok"
        echo ""
    else
        echo "Test failed"
        echo ""
    fi
    if [ $val1 -ne $val2 ]; then
        echo --- ERROR RETURN VALUE ---
        echo expected $val2 but got $val1
    fi

    echo Test 44 :
    ./42sh -c "true | false" > file1
    val1=$?
    bash --posix -c "true | false" > file2
    val2=$?
    diff -u file1 file2
    res=$?
    if [ $res -eq 0 ]; then
        echo "Assert ok"
        echo ""
    else
        echo "Test failed"
        echo ""
    fi
    if [ $val1 -ne $val2 ]; then
        echo --- ERROR RETURN VALUE ---
        echo expected $val2 but got $val1
    fi

    echo Test 45 :
    ./42sh -c "false | true" > file1
    val1=$?
    bash --posix -c "false | true" > file2
    val2=$?
    diff -u file1 file2
    res=$?
    if [ $res -eq 0 ]; then
        echo "Assert ok"
        echo ""
    else
        echo "Test failed"
        echo ""
    fi
    if [ $val1 -ne $val2 ]; then
        echo --- ERROR RETURN VALUE ---
        echo expected $val2 but got $val1
    fi
    
    echo Test 46 :
    ./42sh -c "cat Makefile | echo coucou" > file1
    val1=$?
    bash --posix -c "cat Makefile | echo coucou" > file2
    val2=$?
    diff -u file1 file2
    res=$?
    if [ $res -eq 0 ]; then
        echo "Assert ok"
        echo ""
    else
        echo "Test failed"
        echo ""
    fi
    if [ $val1 -ne $val2 ]; then
        echo --- ERROR RETURN VALUE ---
        echo expected $val2 but got $val1
    fi
    
    echo Test 47 :
    ./42sh -c "cat Makefile | tr s Z" > file1
    val1=$?
    bash --posix -c "cat Makefile | tr s Z" > file2
    val2=$?
    diff -u file1 file2
    res=$?
    if [ $res -eq 0 ]; then
        echo "Assert ok"
        echo ""
    else
        echo "Test failed"
        echo ""
    fi
    if [ $val1 -ne $val2 ]; then
        echo --- ERROR RETURN VALUE ---
        echo expected $val2 but got $val1
    fi
    
    echo Test 48 :
    ./42sh -c "cat Makefile | tr s Z | grep Z" > file1
    val1=$?
    bash --posix -c "cat Makefile | tr s Z | grep Z" > file2
    val2=$?
    diff -u file1 file2
    res=$?
    if [ $res -eq 0 ]; then
        echo "Assert ok"
        echo ""
    else
        echo "Test failed"
        echo ""
    fi
    if [ $val1 -ne $val2 ]; then
        echo --- ERROR RETURN VALUE ---
        echo expected $val2 but got $val1
    fi
    
    echo Test 49 :
    ./42sh -c "if ct Makefile; then echo fine; else echo ciao; echo bonsoir; fi" > file1
    val1=$?
    bash --posix -c "if ct Makefile; then echo fine; else echo ciao; echo bonsoir; fi" > file2
    val2=$?
    diff -u file1 file2
    res=$?
    if [ $res -eq 0 ]; then
        echo "Assert ok"
        echo ""
    else
        echo "Test failed"
        echo ""
    fi
    if [ $val1 -ne $val2 ]; then
        echo --- ERROR RETURN VALUE ---
        echo expected $val2 but got $val1
    fi
    
    echo Test 50 :
    ./42sh -c "if true; then cat Makefile; else echo non; fi; cat br; if true; false; then echo y; elif false; then echo j; else echo yes; fi" > file1
    val1=$?
    bash --posix -c "if true; then cat Makefile; else echo non; fi; cat br; if true; false; then echo y; elif false; then echo j; else echo yes; fi" > file2
    val2=$?
    diff -u file1 file2
    res=$?
    if [ $res -eq 0 ]; then
        echo "Assert ok"
        echo ""
    else
        echo "Test failed"
        echo ""
    fi
    if [ $val1 -ne $val2 ]; then
        echo --- ERROR RETURN VALUE ---
        echo expected $val2 but got $val1
    fi
    
    echo Test 51 :
    ./42sh -c "echo -e hello\\\n; if cat br; then echo hey | tr y R; else echo non; fi" > file1
    val1=$?
    bash --posix -c "echo -e hello\\\n; if cat br; then echo hey | tr y R; else echo non; fi" > file2
    val2=$?
    diff -u file1 file2
    res=$?
    if [ $res -eq 0 ]; then
        echo "Assert ok"
        echo ""
    else
        echo "Test failed"
        echo ""
    fi
    if [ $val1 -ne $val2 ]; then
        echo --- ERROR RETURN VALUE ---
        echo expected $val2 but got $val1
    fi
    
    echo Test 52 :
    ./42sh -c "if echo hey; then echo i; else cat Makefile | tr s E | grep E; fi" > file1
    val1=$?
    bash --posix -c "if echo hey; then echo i; else cat Makefile | tr s E | grep E; fi" > file2
    val2=$?
    diff -u file1 file2
    res=$?
    if [ $res -eq 0 ]; then
        echo "Assert ok"
        echo ""
    else
        echo "Test failed"
        echo ""
    fi
    if [ $val1 -ne $val2 ]; then
        echo --- ERROR RETURN VALUE ---
        echo expected $val2 but got $val1
    fi
    
    echo Test 53 :
    ./42sh -c "if true; then cat Makefile | tr s Z; fi" > file1
    val1=$?
    bash --posix -c "if true; then cat Makefile | tr s Z; fi" > file2
    val2=$?
    diff -u file1 file2
    res=$?
    if [ $res -eq 0 ]; then
        echo "Assert ok"
        echo ""
    else
        echo "Test failed"
        echo ""
    fi
    if [ $val1 -ne $val2 ]; then
        echo --- ERROR RETURN VALUE ---
        echo expected $val2 but got $val1
    fi
    
    echo Test 54 :
    ./42sh -c "cat Makefile | tr s Z | grep Z | tr Z s" > file1
    val1=$?
    bash --posix -c "cat Makefile | tr s Z | grep Z | tr Z s" > file2
    val2=$?
    diff -u file1 file2
    res=$?
    if [ $res -eq 0 ]; then
        echo "Assert ok"
        echo ""
    else
        echo "Test failed"
        echo ""
    fi
    if [ $val1 -ne $val2 ]; then
        echo --- ERROR RETURN VALUE ---
        echo expected $val2 but got $val1
    fi
    
    echo Test 55 :
    ./42sh -c "cat Makefile | tr s Z | grep Z | tr Z s" > file1
    val1=$?
    bash --posix -c "cat Makefile | tr s Z | grep Z | tr Z s" > file2
    val2=$?
    diff -u file1 file2
    res=$?
    if [ $res -eq 0 ]; then
        echo "Assert ok"
        echo ""
    else
        echo "Test failed"
        echo ""
    fi
    if [ $val1 -ne $val2 ]; then
        echo --- ERROR RETURN VALUE ---
        echo expected $val2 but got $val1
    fi
    
    echo Test 56 :
    ./42sh -c "ct Makefile | echo Hey ca la zone; echo oula oule | tr e A | grep e" > file1
    val1=$?
    bash --posix -c "ct Makefile | echo Hey ca la zone; echo oula oule | tr e A | grep e" > file2
    val2=$?
    diff -u file1 file2
    res=$?
    if [ $res -eq 0 ]; then
        echo "Assert ok"
        echo ""
    else
        echo "Test failed"
        echo ""
    fi
    if [ $val1 -ne $val2 ]; then
        echo --- ERROR RETURN VALUE ---
        echo expected $val2 but got $val1
    fi

    echo Test 58 :
    ./42sh -c "cd src/; ls" > file1
    val1=$?
    bash --posix -c "cd src/; ls" > file2
    val2=$?
    diff -u file1 file2
    res=$?
    if [ $res -eq 0 ]; then
        echo "Assert ok"
        echo ""
    else
        echo "Test failed"
        echo ""
    fi
    if [ $val1 -ne $val2 ]; then
        echo --- ERROR RETURN VALUE ---
        echo expected $val2 but got $val1
    fi
    
    echo Test 59 :
    ./42sh -c "cd src/; ls; cd eval_ast; ls" > file1
    val1=$?
    bash --posix -c "cd src/; ls; cd eval_ast; ls" > file2
    val2=$?
    diff -u file1 file2
    res=$?
    if [ $res -eq 0 ]; then
        echo "Assert ok"
        echo ""
    else
        echo "Test failed"
        echo ""
    fi
    if [ $val1 -ne $val2 ]; then
        echo --- ERROR RETURN VALUE ---
        echo expected $val2 but got $val1
    fi
    
    echo Test 61 :
    ./42sh -c "for a do echo cc; done" > file1
    val1=$?
    bash --posix -c "for a do echo cc; done" > file2
    val2=$?
    diff -u file1 file2
    res=$?
    if [ $res -eq 0 ]; then
        echo "Assert ok"
        echo ""
    else
        echo "Test failed"
        echo ""
    fi
    if [ $val1 -ne $val2 ]; then
        echo --- ERROR RETURN VALUE ---
        echo expected $val2 but got $val1
    fi
    
    echo Test 62 :
    ./42sh -c "for a; do echo cc; done" > file1
    val1=$?
    bash --posix -c "for a; do echo cc; done" > file2
    val2=$?
    diff -u file1 file2
    res=$?
    if [ $res -eq 0 ]; then
        echo "Assert ok"
        echo ""
    else
        echo "Test failed"
        echo ""
    fi
    if [ $val1 -ne $val2 ]; then
        echo --- ERROR RETURN VALUE ---
        echo expected $val2 but got $val1
    fi
    
    echo Test 63 :
    ./42sh -c "for a in a b cd ouaf; do echo cc; done" > file1
    val1=$?
    bash --posix -c "for a in a b cd ouaf; do echo cc; done" > file2
    val2=$?
    diff -u file1 file2
    res=$?
    if [ $res -eq 0 ]; then
        echo "Assert ok"
        echo ""
    else
        echo "Test failed"
        echo ""
    fi
    if [ $val1 -ne $val2 ]; then
        echo --- ERROR RETURN VALUE ---
        echo expected $val2 but got $val1
    fi

    echo Test 64 :
    ./42sh -c "echo ok <> file1.txt" | tr ' ' '\n' > file1
    val1=$?
    bash --posix -c "echo ok <> file2.txt" | tr ' ' '\n' > file2
    val2=$?
    diff -u file1 file2
    res=$?
    if [ $res -eq 0 ]; then
        echo "Assert 1 ok"
        echo ""
    else
        echo "Test 1 failed"
        echo ""
    fi
    diff -u file1.txt file2.txt
    res=$?
    if [ $res -eq 0 ]; then
        echo "Assert 2 ok"
        echo ""
    else
        echo "Test 2 failed"
        echo ""
    fi
    if [ $val1 -ne $val2 ]; then
        echo --- ERROR RETURN VALUE --- 
        echo expected $val2 but got $val1
        echo ""
    fi

    echo Test 65 :
    ./42sh -c "cat <> file1.txt" | tr ' ' '\n' > file1
    val1=$?
    bash --posix -c "cat <> file2.txt" | tr ' ' '\n' > file2
    val2=$?
    diff -u file1 file2
    res=$?
    if [ $res -eq 0 ]; then
        echo "Assert 1 ok"
        echo ""
    else
        echo "Test 1 failed"
        echo ""
    fi
    diff -u file1.txt file2.txt
    res=$?
    if [ $res -eq 0 ]; then
        echo "Assert 2 ok"
        echo ""
    else
        echo "Test 2 failed"
        echo ""
    fi
    if [ $val1 -ne $val2 ]; then
        echo --- ERROR RETURN VALUE --- 
        echo expected $val2 but got $val1
    fi
    
    echo Test 66 :
    ./42sh -c "if true then echo true; else echo false; fi" | tr ' ' '\n' > file1
    val1=$?
    bash --posix -c "if true then echo true; else echo false; fi" | tr ' ' '\n' > file2
    val2=$?
    diff -u file1 file2
    res=$?
    if [ $res -eq 0 ]; then
        echo "Assert 1 ok"
        echo ""
    else
        echo "Test 1 failed"
        echo ""
    fi
    diff -u file1.txt file2.txt
    res=$?
    if [ $res -eq 0 ]; then
        echo "Assert 2 ok"
        echo ""
    else
        echo "Test 2 failed"
        echo ""
    fi
    if [ $val1 -ne $val2 ]; then
        echo --- ERROR RETURN VALUE --- 
        echo expected $val2 but got $val1
        echo ""
    fi

    echo Test 67 :
    ./42sh -c "if true; echo oui; echo true; else echo false; fi" | tr ' ' '\n' > file1
    val1=$?
    bash --posix -c "if true; echo oui; echo true; else echo false; fi" | tr ' ' '\n' > file2
    val2=$?
    diff -u file1 file2
    res=$?
    if [ $res -eq 0 ]; then
        echo "Assert 1 ok"
        echo ""
    else
        echo "Test 1 failed"
        echo ""
    fi
    diff -u file1.txt file2.txt
    res=$?
    if [ $res -eq 0 ]; then
        echo "Assert 2 ok"
        echo ""
    else
        echo "Test 2 failed"
        echo ""
    fi
    if [ $val1 -ne $val2 ]; then
        echo --- ERROR RETURN VALUE --- 
        echo expected $val2 but got $val1
        echo ""
    fi

    rm file1
    rm file2
    rm file1.txt
    rm file2.txt
    
fi
