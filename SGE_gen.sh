if pip list | grep quom > /dev/null
then
    printf "Generating SGE.hpp\n";
    quom SGE_STRUCTURE.hpp SGE.hpp -s "-> stitch <-";
else
    printf "Python 'quom' library is required";
    printf "Can be installed using '\$pip install quom'";
fi
