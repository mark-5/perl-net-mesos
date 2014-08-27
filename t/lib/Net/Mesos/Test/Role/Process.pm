package Net::Mesos::Test::Role::Process;
use Symbol;
use Moo::Role;
use strict;
use warnings;

use Net::Mesos::Channel;

has channel => (
    is      => 'ro',
    default => sub { Net::Mesos::Channel->new },
);

has return => (
    is      => 'rw',
    default => sub { {} },
);

sub create_method {
    my ($self, $method, $code) = @_;
    my $package = ref $self || $self;
    no strict 'refs';
    *{qualify($method, ref $self)} = $code;
}

our $AUTOLOAD;
sub AUTOLOAD {
    (my $method = $AUTOLOAD) =~ s{.*::}{};
    my ($self, @args) = @_;
    $self->return->{$method} = \@args;
}

1;
