#!/usr/bin/python

import smtplib, sys

sender = 'hsko@rcf.rhic.bnl.gov'
receivers = ['jknim19@gmail.com']

message = """From: From Your Wench <hsko@rcf.rhic.bnl.gov>
To: To M'Lord <jknim19@gmail.com>
Subject: The Merge is done, M'Lord

The Merge is done, M'Lord.

Yours sincerely,
Your Wench
"""

try:
   smtpObj = smtplib.SMTP('localhost')
   smtpObj.sendmail(sender, receivers, message)         
   print "Successfully sent email"
except SMTPException:
   print "Error: unable to send email"

sys.exit()
