#!/usr/bin/env bash

export PYTHON_EGG_CACHE=./myeggs
source /home/wfuser/.hadoop_env.sh

EMAILS="alex.haden@txodds.com" # Separate emails by space

send_email() {
    echo "$1" | mail -s "$2" "$EMAILS"
}

xml2_us_missing_odds() {
# expected input: sport, x_sportid, odds_type, otid, book, bid, updates, latest_update, time_alert
    QUERY="select sport, x_sportid, odds_type, otid, book, bid, updates, latest_update, time_alert from data_quality.bd_xml2_us_missing_odds
order by bid, x_sportid, otid"
    if ! impala-shell -B -o checks_xml2_odds.txt --output_delimiter=',' -q "$QUERY"; then
        send_email "ERROR: $QUERY failed" "TXHADOOP ALERT for $HOSTNAME"
        continue
    fi
    RETURNS=$(wc -l < checks_xml2_odds.txt) # Line count
    awk -F',' '{ print NR ".", $5, "(book id", $6 "),", $1, "(sport id", $2 "),", $3, "(odds type id",  $4 ")." , "Updates:", $7 ".", "Last update (UK):", $8 ", time alert (UK):", $9 }' checks_xml2_odds.txt > combined_xml2_output.txt
    echo "" >> combined_xml2_output.txt
    echo "" >> combined_xml2_output.txt
    echo "" >> combined_xml2_output.txt
    echo "This email contains odds types which have not been used for a significant time period, which has raised an alert." >> combined_xml2_output.txt
    BODY=$(cat combined_xml2_output.txt)
    if [[ $RETURNS > 1 ]]; then
        send_email "$BODY" "XML2 US potential missing odds types identified"
    fi
    if [[ $RETURNS = 1 ]]; then
        send_email "$BODY" "XML2 US potential missing odds type identified"
    fi
}

xml2_us_missing_odds

xml2_soccer_missing_odds() {
# expected input: sport, x_sportid, odds_type, otid, book, bid, updates, latest_update, time_alert
    QUERY="select sport, x_sportid, odds_type, otid, book, bid, updates, latest_update, time_alert from data_quality.bd_xml2_soccer_missing_odds
order by bid, x_sportid, otid"
    if ! impala-shell -B -o checks_xml2_odds.txt --output_delimiter=',' -q "$QUERY"; then
        send_email "ERROR: $QUERY failed" "TXHADOOP ALERT for $HOSTNAME"
        continue
    fi
    RETURNS=$(wc -l < checks_xml2_odds.txt) # Line count
    awk -F',' '{ print NR ".", $5, "(book id", $6 "),", $1, "(sport id", $2 "),", $3, "(odds type id",  $4 ")." , "Updates:", $7 ".", "Last update (UK):", $8 ", time alert (UK):", $9 }' checks_xml2_odds.txt > combined_xml2_output.txt
    echo "" >> combined_xml2_output.txt
    echo "" >> combined_xml2_output.txt
    echo "" >> combined_xml2_output.txt
    echo "This email contains odds types which have not been used for a significant time period, which has raised an alert." >> combined_xml2_output.txt
    BODY=$(cat combined_xml2_output.txt)
    if [[ $RETURNS > 1 ]]; then
        send_email "$BODY" "XML2 Soccer potential missing odds types identified"
    fi
    if [[ $RETURNS = 1 ]]; then
        send_email "$BODY" "XML2 Soccer potential missing odds type identified"
    fi
}

xml2_soccer_missing_odds

