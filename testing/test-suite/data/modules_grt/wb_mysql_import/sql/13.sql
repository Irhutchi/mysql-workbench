CREATE TABLE t (f01 TIMESTAMP ON UPDATE CURRENT_TIMESTAMP
DEFAULT CURRENT_TIMESTAMP,
f02 INTEGER DEFAULT 1,
f03 VARCHAR(10) default '',
f04 VARCHAR(10) default 'defval',
f05 DATE default DATE '01.01.2000',
no_default_val VARCHAR(10)
);
