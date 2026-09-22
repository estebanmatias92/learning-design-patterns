/* Shared quiz widget: instant feedback, tight loop. No deps. */
(function () {
  function wire(scope) {
    scope.querySelectorAll('[data-quiz]').forEach(function (quiz) {
      var feedback = quiz.querySelector('[data-feedback]');
      var buttons = Array.prototype.slice.call(quiz.querySelectorAll('[data-answer]'));
      buttons.forEach(function (btn) {
        btn.addEventListener('click', function () {
          var ok = btn.getAttribute('data-correct') === 'true';
          buttons.forEach(function (b) {
            b.setAttribute('disabled', 'disabled');
            if (b.getAttribute('data-correct') === 'true') b.classList.add('correct');
          });
          if (!ok) btn.classList.add('wrong');
          if (feedback) {
            feedback.classList.remove('ok', 'no');
            feedback.classList.add(ok ? 'ok' : 'no');
            feedback.textContent = ok
              ? 'Correct. ' + (quiz.getAttribute('data-why') || '')
              : 'Not quite — ' + (quiz.getAttribute('data-why') || 're-read the snippet above and try the next one.');
          }
        });
      });
    });

    // Simple step-through for dispatch tracers
    scope.querySelectorAll('[data-steps]').forEach(function (box) {
      var steps = Array.prototype.slice.call(box.querySelectorAll('.step'));
      var btn = box.querySelector('[data-next-step]');
      var i = 0;
      steps.forEach(function (s, idx) { s.style.display = idx === 0 ? 'grid' : 'none'; });
      if (!btn) return;
      btn.addEventListener('click', function () {
        if (i < steps.length - 1) {
          i += 1;
          steps[i].style.display = 'grid';
          if (i === steps.length - 1) btn.setAttribute('disabled', 'disabled');
        }
      });
    });
  }
  if (document.readyState === 'loading') {
    document.addEventListener('DOMContentLoaded', function () { wire(document); });
  } else {
    wire(document);
  }
})();
