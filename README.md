# get_options
## int  get_options(char **argv, t_options *options, char *valid_options, int *offset)
`argv` array of program arguments.
`options` reference to a t_options and array of t_option which should populated with options and their values.
`offset` offset of arguments which are not options.
`valid_options` a string containing valid option manifest. `valid_options` format: **`<[ .: ]option>`** where **`.`** means boolean and **`:`** means keyvalue option, e.g. **`".boolean:keyvalue"`**

`-b` ≡ `--boolean` .
`-k value` ≡ `--key value` .

*get_options() returns 0 if success, err != 0 otherwise.*

#### CONVENTIONS:
- we distinguish two types of options: `boolean` and `keyvalue` ones.
- short keyvalue options can't be mixed with short boolean options, e.g. `$> command -kb file` where ****b** is boolean** and **k is keyvalue**.
- the next argument after a keyvalue option is taken as the value.
- first character of every option should be **unique**. --key ≡ -k

## char *read_option(t_options options, char *option)
if option is **boolean**:
-	**a `NULL` return means that option is not set.**
-	**a `return != NULL` means that option is set.**

if option is **keyvalue**, if option is set the value is returned otherwise `NULL` is returned.

## void  destroy_options(t_options options)
free up allocated t_options structure and its entries.

	typedef struct	s_option
    {
	    char *option;
	    char type;
	    char *value;
    }				t_option;
    
    typedef t_option*	t_options;
## errors

    # define NO_VALUE_SPECIFIED 1 // let `type` be a key-value option. examples: "$> command --type"
    # define UNRECOGNIZED_OPTION 2 // when option is not defined in the valid_options string
    # define MIXED_FLAGS_TYPE 3 // let `k` be a key-value option and `b` a boolean option. examples: "$> command -ob"
    # define SYNTAX_ERROR 4 // for valid_options string when option is empty string or not unique options.
    # define RESOURCE_ERROR -5
