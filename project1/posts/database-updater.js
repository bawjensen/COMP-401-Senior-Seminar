var Firebase    = require('firebase'),
    fs          = require('fs'),
    marked      = require('marked'),
    path        = require('path');

// Connect to database
var fb = new Firebase("https://personal-blog.firebaseio.com");

// Configure the markdown converter
marked.setOptions({
    renderer: new marked.Renderer(),
    gfm: true,
    tables: true,
    breaks: false,
    pedantic: false,
    sanitize: true,
    smartLists: true,
    smartypants: false
});

var initialDir = '.';

// Read the contents of the enclosing directory
fs.readdir(initialDir, function(err, subDirectories) {
    if (err) throw err;

    // Iterate over the (potential) directories in the enclosing dir
    subDirectories.forEach(function(topicSubDir) {
        var topicSubDir = subDirectories[i];

        // Fetch stats for potential dir
        fs.stat(topicSubDir, (function(topicSubDir, err, stats) {
            if (err) throw err;

            // Check if potential dir is a dir and not a file
            if (stats.isDirectory()) {
                var newDir = path.join(initialDir, topicSubDir);

                // Read its contents
                fs.readdir(newDir, function(err, files) {

                    // For every post in a topic
                    files.forEach(function(file) {
                        var fileExt = path.extname(file);
                        var fileBase = path.basename(file, fileExt);

                        if (fileExt === '.md') {
                            fs.readFile(path.join(newDir, file), 'utf8', function(err, mdFile) {
                                if (err) throw err;

                                // Convert the markdown to html
                                var html = marked(mdFile);

                                // Find the correct field in database
                                var topic = fb.child('topics').child(topicSubDir);

                                // Add the html
                                topic.child('posts').child(fileBase).set({
                                    title: fileBase,
                                    text: html,
                                    preview: html.slice(0, 200)
                                });
                            });
                        }
                        else {
                            console.log('File wasn\'t markdown');
                        }
                    })
                });
            }
        }).bind(null, topicSubDir)); // Creating a closure for the callback
    });
});