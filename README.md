# Call-Schedule
Get the optimal schedule given a set of users and for each one the probability to answer in a given period of the time


# File Format
Agents number (int) <br />
Max calls per interval (int)<br />
Interval number (int) (m)<br />
Customers number (int) (k)<br />
n1 n2 n4 .... nm<br />
.. .. .. .... ..<br />
.. .. .. .... ..<br />
.<br />
.<br />
.<br />
n1 n2 n4 .... nm <br />

# Observations
- Table values are float
- Max m columns and k rowns
- Must be one space separated


# Usage

1 - Instal Google Or Tools (https://developers.google.com/optimization/introduction/installing/binary)

2 - Clone this repo at root of the Google Or Tools folder

3 - Create Your data file

4 - In the root of Google Or tools run 
<pre>
	make ccc EX=Call-Schedule/call_schedule.cc
</pre>

5 - Again in the Google Or tolls root run the command above to see your schedule
<pre>
	./bin/call_schedule < ./call_schedule/data/sample.txt
</pre>