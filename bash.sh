####################### 6.7.16 ############################

string=""
avg=0
while read id1 avg1;do
	while read id2 avg2;do
		if [[ $id1 == $id2 ]];then
			avg=$(( $avg1+$avg2 ))
			string+="$avg $id2\n"
		fi
	done < $2
done < $1


###################### 6.8.14 ###########################

echo -e $string | sort -rn | head -5 | cut -d" " -f2

for file in `ls | grep "Age"`;do
	string=""
	age=`echo $file | cut -d'e' -f2 | cut -d'.' -f1`
	while read id name hight weight weist;do
		bmi=$(($weight*10000/($hight*$hight)))
		if [[ $# -eq 1 ]];then
			if [[ $bmi -gt $1 ]];then
				string+="\n$id $age"
			fi
		else
			if [[ $# -eq 2 ]];then
				if [[ ($bmi -gt $1) && ($bmi -lt $2) ]];then
					string+="\n$id $age"
				fi
			fi
		fi
	done < $file
	echo -e $string | tail -n +2
done


###################### 8.7.15 ###########################

count=0
string=""

while read id name hedva1 c_course english maarhot algebra;do

	if [[ ($c_course -gt 54) && ($maarhot -gt 54) ]];then
		string+="`echo $((($c_course+$maarhot)/2))` $name $id\n"
		let count++
	fi

done < <(cat $1 | tail -n +2 | tr '-' '0')

echo -e $string | sort -rn | cut -d" " -f2- > MatamStudents.data
echo "Sum: $count Students." >> MatamStudents.data

###################### 18.6.14 ###########################

fly=`cat flights.fly | grep "$1 $2" | cut -d" " -f3`
fly=`echo $fly | cut -c1-4`
string=""
name=""
price=""

for f in `ls ./passengers`;do
	if [ `cat passengers/$f | cut -d" " -f1` == "$fly" ];then
		name=`echo $f | cut -d"." -f1 | tr '_' ' '`
		price=`cat passengers/$f | cut -d" " -f2`
		string+="$name $price\n"
	fi
done

echo -e $string | sort -k 3 -r | head -1

i=0
for f in `echo -e $string`;do
	let i++
	if [[ $(($i%3)) -eq 0 ]];then
		let avg+=$f
	fi
done

avg=$(($avg/$(($i/3))))
echo "Average: $avg"

###################### 14.8.13 ###########################

string=""
numOfCourses=$((`cat $1 | grep "StudentId" | tr '\t' '\n' | wc -l`-2))
for r in `seq 3 $((2+$numOfCourses))`;do
	cnt=`cat $1 | cut -d$'\t' -f$r | grep '-' | wc -l`
	course=`cat $1 | cut -d$'\t' -f$r | head -1`
	if [[ $cnt -ne 0 ]];then
		string+="$course $cnt\n"
	fi
done

echo -e $string | sort -k 2 -n | tail -n +2
