var CURRENT_ROUTE = window.location.pathname;

// ==================================== Portfolio scripts ============================

function initializePortfolio() {
    $('#project-list li').click(function() {
        var targetId = $(this).attr('id');
        var newId = '#' + targetId + '-info';
        $('#project-info > div').hide();

        var $newDiv = $(newId);

        $newDiv.show().parent('#project-info').height($newDiv.height());
    });
}

// ==================================== Main page scripts ============================

// Separated function to scroll smoothly to the blog div from anywhere on page
function scrollToBlog() {
    $('html, body').animate({
        scrollTop: $('#blog-container').offset().top
    }, 250);
}

// Global blog variable
var blog = {};

// Initialization call to set everything up
function initializeMainPage() {
    // When any state transition is clicked, call the corresponding function
    $(document).on('click', '.state-transition', function(evt) {
        var transitionId = $(this).data('state');

        if (transitionId in blog.state.transitions) {
            blog.state.transitions[transitionId](evt);
        }
    });

    // Set up database connection
    var topics = new Firebase("https://personal-blog.firebaseio.com/");

    // When a value is reported by the database
    topics.on("value", function(data) {
        var topicsObj = data.val() ? data.val().topics : {};

        // Load template
        var topicLinksTemplate = blogTemplate({ topicsObj: topicsObj });

        // Set up and fill container for the HTMLs of the fleshed-out templates
        var topicHtmls = {};
        for (var key in topicsObj) {
            topicHtmls[key] = topicTemplate({ topic: topicsObj[key] });
        }

        // All potential states and their transitions
        blog.states = {
            // Page is loaded, but no action has been taken with respect to the blog
            'first': {
                transitions: {
                    // The introduction to the blog should happen
                    'intro': function(evt) {
                        // Fetch the HTML of the given topic and create an element out of it
                        var $newDiv = $($.parseHTML(topicLinksTemplate));

                        $newDiv.appendTo('#content');

                        scrollToBlog();

                        // Set the new state
                        blog.state = blog.states.second;
                    }
                }
            },
            // The blog has been 'opened' and the user is looking at the topics of the blog
            'second': {
                transitions: {
                     // The 'home' option has been selected, meaning the blog should close
                    'home': function(evt) {
                        $('#blog-container').remove();

                        // Set the new state
                        blog.state = blog.states.first;
                    },

                    // The introduction to the blog should happen
                    'intro': scrollToBlog,

                    // A topic has been selected, and should open up with its posts showing
                    'topic': function(evt) {
                        // Fetch the HTML of the given topic and create an element out of it
                        var $newDiv = $($.parseHTML(topicHtmls[evt.target.id]));

                        var topics = $('#topics-container');

                        // Manually set attributes to remove buginess with animation
                        topics.css('margin-left', topics.css('margin-left'));
                        topics.css('float', 'left');
                        topics.css('display', 'block');

                        // Animate the opening of the posts
                        topics.animate({
                            marginLeft: 40,
                            marginRight: 40,
                            width: 200
                        }, 250, function after() {
                            $newDiv.appendTo($('#blog-container'));
                        });

                        // Set the new state
                        blog.state = blog.states.third;
                    }
                }
            },
            // A topic for the blog has been selected, and the user is viewing the posts in that topic
            'third': {
                transitions: {
                     // The 'home' option has been selected, meaning the blog should close
                    'home': function(evt) {
                        $('#blog-container').remove();

                        // Set the new state
                        blog.state = blog.states.first;
                    },

                    // The introduction to the blog should happen
                    'intro': scrollToBlog,

                    // A topic has been selected, and should open up with its posts showing
                    'topic': function(evt) {
                        // Fetch the HTML of the given topic and create an element out of it
                        var $newDiv = $($.parseHTML(topicHtmls[evt.target.id]));

                        $('#posts').replaceWith($newDiv);
                    },

                    // A specific post within a topic has been selected, and should open with its full text
                    'post': function(evt) {
                        var $clicked = $(evt.target);

                        $clicked.closest('.post').find('.preview, .text').toggle();

                        // Set which post is currently showing
                        blog.state.$showing = $clicked;

                        // Set the new state
                        blog.state = blog.states.fourth;
                    },

                    // The close option has been selected for a topic
                    'close': function(evt) {
                        $('#posts').remove();
                        $('#topics-container').attr('style', '');

                        // Set the new state
                        blog.state = blog.states.second;
                    }
                }
            },
            // The user is looking at the full text of a specific blog post
            'fourth': {
                transitions: {
                     // The 'home' option has been selected, meaning the blog should close
                    'home': function(evt) {
                        $('#blog-container').remove();

                        // Set the new state
                        blog.state = blog.states.first;
                    },

                    // The introduction to the blog should happen
                    'intro': scrollToBlog,

                    // A topic has been selected, and should open up with its posts showing in place of the old topic's
                    'topic': function(evt) {
                        // Fetch the HTML of the given topic and create an element out of it
                        var $newDiv = $($.parseHTML(topicHtmls[evt.target.id]));

                        $('#posts').replaceWith($newDiv);
                    },

                    // An alternate post has been selected while a certain one is already open
                    'post': function(evt) {
                        var $clicked = $(evt.target).closest('.post');

                        $clicked.find('.preview, .text').toggle();

                        if (blog.state.$showing && ($clicked[0] == blog.state.$showing[0])) {
                            // No posts are open, so go back to the third state
                            blog.state = blog.states.third;
                        }
                        else if (blog.state.$showing) {
                            blog.state.$showing.find('.preview, .text').toggle();
                            blog.state.$showing = $clicked;
                        }
                        else {
                            blog.state.$showing = $clicked;
                        }
                    },

                    // The close option has been selected for a topic, going back to state 2
                    'close': function(evt) {
                        $('#posts').remove();
                        $('#topics-container').attr('style', '');

                        // Set the new state
                        blog.state = blog.states.second;
                    }
                },
                // Initially no posts are showing
                $showing: null
            }
        };

        // Initialize the blog as being in the first state
        blog.state = blog.states.first;
    });
}

// ==================================== OnLoad scripts ===============================

// Only initialize scripts for the page that is currently active
$(function() {
    if (CURRENT_ROUTE.match('portfolio')) {
        initializePortfolio();
    }
    else if (CURRENT_ROUTE.match('/')) {
        initializeMainPage();
    }
});