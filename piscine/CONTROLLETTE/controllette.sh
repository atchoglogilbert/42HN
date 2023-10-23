# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    controllette.sh                                    :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/21 13:44:29 by katchogl          #+#    #+#              #
#    Updated: 2022/08/18 23:27:15 by katchogl         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!bin/bash
echo " ";
DIRS=$( find . -type d -name 'ex*' | tr '\n' ' ';);
IFS=' ' read -r -a DIRS_ARR <<< "$DIRS" 

TOTAL_COUNT_EXTRA_FILES=0;
TOTAL_COUNT_FT_FILES=0;
TOTAL_COUNT_DIRS=0;
	
for DIR in ${DIRS_ARR[@]}
do
	TOTAL_COUNT_DIRS=$((TOTAL_COUNT_DIRS+1))

    EXTRA_FILES=$( find "$DIR" -maxdepth 1 -type f  -not -name '.gitignore' -not -name 'controllette.sh' -not -name 'ft_*' -execdir basename {}  \; | tr '\n' ' ';);
    FT_FILES=$( find "$DIR" -maxdepth 1 -type f  -name 'ft_*' -execdir basename {}  \; | tr '\n' ' ';);
	DIR_OUT="";

	if [ "$DIR" == "." ]
	then
		DIR_OUT="ROOT";
	else
		DIR_OUT=$(echo "$DIR" | tr "./" " " | xargs );
    fi

	COUNT=0;
	REPORT="";
	if [ "$EXTRA_FILES" == "" ]
	then
		REPORT="CLEAN"
	else
		IFS=' ' read -r -a EXTRA_FILES_ARR <<< "$EXTRA_FILES";

		for EXTRA_FILE in ${EXTRA_FILES_ARR[@]}
		do
			COUNT=$((COUNT+1));
         	TOTAL_COUNT_EXTRA_FILES=$((TOTAL_COUNT_EXTRA_FILES+1))
		done

		REPORT="FOUND $COUNT EXTRA FILE(S): $EXTRA_FILES"   
	fi

	COUNT_FT=0;
	REPORT_FT="";

	if [ "$DIR_OUT" != "ROOT" ]
	then 
		if [ "$FT_FILES" == "" ]
		then
			REPORT_FT="ft. FUNCTION MISSING!"
		else
			IFS=" " read -r -a FT_FILES_ARR <<< "$FT_FILES";

			for FT_FILE in ${FT_FILES_ARR[@]}
			do
				if [ "$FT_FILE" != ""  ] && [ "$FT_FILE" != " " ]
				then 
					COUNT_FT=$((COUNT_FT+1));
                  	TOTAL_COUNT_FT_FILES=$((TOTAL_COUNT_FT_FILES+1))
				fi
			done

			REPORT_FT="$COUNT_FT ft. FILE(S) FOUND: $FT_FILES"   
		fi
	fi

	OUT="$DIR_OUT: $REPORT | $REPORT_FT ";
	echo "$OUT";
done

# default
# .gitignore
TEST=-1; # controllette.sh not added
TEST2=-1; # .gitignore not added
RESULT=$( find . -maxdepth 1 -type f -name '.gitignore*' | cut -c 3- | xargs; );
if [ "$RESULT" == ".gitignore" ]
then
    RESULT_2=$(cat .gitignore | tr "\n", " " | xargs ; );
	IFS=" " read -r -a RESULT_2_ARR <<< "$RESULT_2";
	for IGNORED_FILE in "${RESULT_2_ARR[@]}"
	do
		if [ "$IGNORED_FILE" == "controllette.sh" ]
		then
			TEST=1;
		elif [ "$IGNORED_FILE" == ".gitignore" ]
		then
			TEST2=1;
		fi
	done
else
	# no .gitignore at all
	TEST=-2; # .controllette.sh not added
	TEST2=-2; # .gitignore not added
fi


if [ $TEST == -1 ] || [ $TEST == -2 ]
then
    if [ $TEST == -1 ]
	then
		echo ".gitignore located.";
	else 
		echo ".gitignore missing. Creating one ...";
		touch .gitignore;
		echo "Created!";
	fi;
	echo "Adding myself ...";
	echo -e "\ncontrollette.sh" >> .gitignore;
	echo "Sucess.";

	if [ $TEST2 == -2 ]
	then
		TEST=-1; #.gitignore should exist  
	fi
fi


if [ $TEST2 == -1 ] || [ $TEST2 == -2 ]
then
    if [ $TEST2 == -1 ]
	then
		echo "Adding .gitgnore";
		echo -e "\n.gitignore" >> .gitignore;
		echo "Sucess.";
	else 
		echo "An error occurred. .gitignore should be present.";
	fi;
fi


echo " ";
STATUS="";
TOTAL_COUNT_SUB_DIRS=$((TOTAL_COUNT_DIRS));
if [ $TOTAL_COUNT_EXTRA_FILES == 0 ] && [ $TOTAL_COUNT_FT_FILES -ge $TOTAL_COUNT_SUB_DIRS ]
then 
	STATUS="GO";
else
	STATUS="NO-GO";
fi
echo "STATUS: $STATUS";