F-Bridge
========
#Introduction

#Software Architecture
RBA (Remote Bridge Agent) pipeline:

```
+-------------+ +-------------+ +----------------------+ +------------+
| Input Queue |-| REST Parser |-| Destination Resolver |-| Rest Proxy |
+-------------+ +-------------+ +----------------------+ +------------+
                                          | |
					  | |
			          +------------------+
				  | Presence Service |
				  +------------------+

```
