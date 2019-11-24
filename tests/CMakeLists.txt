

add_custom_target(check-all-libs
   DEPENDS check-obcl
)

add_custom_target(check
   DEPENDS check-all-libs
)

