SELECT COUNT(*) FROM ASSIGNMENT
WHERE strftime('%Y', StartDate) = '2011' OR strftime('%Y', TermDate) = '2012'