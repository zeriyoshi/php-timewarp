<?php

\TimeWarp\timewarp_set(new class () implements \TimeWarp\ProviderInterface {
    private ?\DateTimeInterface $now = \null;

    public function provide(string $datetime = 'now', ?\DateTimeZone $timezone = \null): \DateTimeInterface
    {
        var_dump($datetime, $timezone);
        return $this->now !== \null ? $this->now : $this->now = new \DateTime();
    }
});


var_dump(\TimeWarp\timewarp_now());
var_dump(\TimeWarp\timewarp_now());
