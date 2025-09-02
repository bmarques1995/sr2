# Priority level

- 1\) Very High (MVP)
- 2\) High (Release)
- 3\) Medium (Upgrade/I have time)

# Features

- 1) [ ] `list`(1): list all installed packages (similar to apt list)
- 2) [ ] `sync`(1): sync list of available packages (similar to apt update)
- 3) [ ] `upgrade`(1): upgrade the system by installing/upgrading packages (similar to apt upgrade)
    - opt:
        - `-d/--dev`(2): add the dev dependencies
        - `-y`(2): automatically confirms the requirements
- 4) [ ] `remove`(1): uninstall a package (similar to apt remove)
    - opt:
        - `-p/--purge`(2): add purge option (similar to the full apt purge)
        - `-y`(2): automatically confirms the requirements
- 5) [ ] `autoremove`(2): remove all unused packages
- 6) [ ] `autoupgrade`(2): upgrade the version of sr2
- 7) [ ] `install`(1): installs a package
    - opt:
        - `-d/--dev`(2): installs the dev dependencies
        - `-y`(2): automatically confirms the requirements
- 8) [ ] `upload`(2): uploads a package
- 9) [ ] `login`(2): log in to a server
    - opt:
        - `-n/--nostr`(3): uses the nostr protocol, send to a nostr relay
        - `-t/--tor`(3): uses TOR connection