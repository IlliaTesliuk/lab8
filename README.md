[![Travis-CI][travis-badge]][travis-builds]

[travis-badge]: https://travis-ci.org/IlliaTesliuk/lab8.svg?branch=master
[travis-builds]: https://travis-ci.org/IlliaTesliuk/lab8/builds

# Laboratory work 8
## HTTP server
### Task
TCP server which receives TCP clients' requests and communicates with them using HTTP protocol.
Server processes only HTTP GET requests.
#### Avaliable HTTP paths:
* `/` - sends json object with information about server
* `/favourites` - sends json list with favourite websites
* `/favorites?{key}={value}` - sends json sublist with websites from `/favourites` list which have field `{key}` set as `{value}`
* `/favorites/{id}` - sends json object from `/favourites` list with id set as `{id}`
* `/file` - reads `data.txt` file from `data/` dircetory, Sends json object with name of file, its size and data
* `/file/data` - sends json object with infromation about amount of numbers in `data.txt` and their average value
### Modules
* Website - describes website
* List - contains search functions for list of websites
* Storage - works with data and files
* Request - processes HTTP request and responces